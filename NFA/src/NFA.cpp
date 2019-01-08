#include "NFA.h"

namespace CyA
{

NFA& NFA::operator=(const NFA& rhs)
{
    if (this == &rhs) return *this;

    set_arranque(rhs.get_arranque());
    set_dfa(rhs.es_dfa());
    set_F(rhs.get_F());
    set_Q(rhs.get_Q());
    set_sigma(rhs.get_sigma());

    return *this;
}


std::ostream& NFA::write(std::ostream& os) const
{
    os << get_Q().size() << std::endl;

    os << get_arranque() << std::endl;

    for (const auto& i: get_Q())
    {
        os << i.get_id() << " " << i.es_aceptacion() << " " << i.get_ntransiciones() << " ";
        for (const auto& j: i.get_delta())
            os << j;
        os << std::endl;
    }

    return os;
}


std::ifstream& NFA::read(std::ifstream& is)
{
    if(definido())  reset();

    std::string fichero;

    std::cout << "Introduce el nombre del fichero: ";
    std::cin >> fichero;

    is.open(fichero);

    if(is.is_open())
    {
        unsigned int nestados;
        unsigned int init;

        is >> (unsigned int&) nestados >> (unsigned int&) init;
        set_arranque(init);

        bool aceptacion;
        bool muerte;
        char entrada;
        unsigned int destino;
        unsigned int id;
        unsigned int ntransiciones;

        for (unsigned int i = 0; i < nestados; i++)
        {
            is >> (unsigned int&) id >> (bool&) aceptacion >> (unsigned int&) ntransiciones;

            estado_t temp(id, aceptacion);

            muerte = true;

            for (unsigned int j = 0; j < ntransiciones; j++)
            {
                is >> (char&) entrada >> (unsigned int&) destino;

                if (entrada != epsilon) sigma_.insert(entrada);

                temp.insert_transicion(entrada, destino);

                if (id != destino || aceptacion)    muerte = false;

                temp.set_muerte(muerte);

            }

            Q_.insert(temp);

            if (aceptacion)
            {
                F_.insert(temp);
            }
        }

        check_dfa();

        is.close();
        std::cout << "Fichero leido correctamente." << std::endl;
    }

    else
        std::cerr << "Error en la apertura del fichero." << std::endl;

    return is;
}

void NFA::leer_cadena() const
{
    bool aceptada = false;
    cadena_t s;
    std::string caminos;

    std::cout << "Cadena de entrada: ";
    std::cin >> s;
    std::cin.clear();

    for (const auto& i: s)
    {
        if(get_sigma().count(i) == 0)
        {
            std::cerr << "La cadena contiene simbolos no pertenecientes al alfabeto." << std::endl;
            return;
        }
    }

    contador = 0;
    analizar_cadena(s, 0, get_arranque(), caminos, aceptada);

    std::cout << std::endl << "Decision Final:" << std::endl;
    std::cout << "Cadena de entrada" << ((aceptada)? " " : " NO ") << "ACEPTADA" << std::endl;

}



void NFA::analizar_cadena(const cadena_t& entrada, size_t posicion, const estado_t& actual, std::string buffer, bool& aceptada) const
{
    if(posicion >= entrada.size())
    {
        mostrar_traza(std::cout, buffer);
        bool flag = get_F().count(actual);
        if(flag)
            aceptada = true;
        std::cout << '\n' << "Cadena de entrada" << ((flag)? " " : " NO ") << "ACEPTADA" << '\n';
        return;
    }

    bool camino_incompleto = true;
    std::set<unsigned int> transiciones;

    buffer += '\n';
    buffer += std::to_string(actual.get_id());

    transiciones = actual.get_transiciones(epsilon);

    if(!transiciones.empty())
    {
        buffer += "\t\t";
        buffer += epsilon;
        camino_incompleto = false;


        for(const auto& destino: transiciones)
        {
            auto it = get_Q().find(destino);
            std::string tmp = "\t\t" +  std::to_string(it->get_id()) ;     //calcular el numero de digitos del id
            buffer += tmp;
            analizar_cadena(entrada, posicion, *it, buffer, aceptada);
            buffer.erase(buffer.size() - tmp.size(), tmp.size());           //borramos el ultimo estado de la recursion
        }
        buffer.erase(buffer.size() - 3, 3);                                 //borramos los tabuladores y ultimo simbolo
    }

    const char simbolo = entrada.at(posicion);

    transiciones = actual.get_transiciones(simbolo);

    if(!transiciones.empty())
    {
        buffer += "\t\t";
        buffer += simbolo;
        camino_incompleto = false;

        for(const auto& destino: transiciones)
        {
            auto it = get_Q().find(destino);
            std::string tmp = "\t\t" + std::to_string(it->get_id());
            buffer += tmp;
            analizar_cadena(entrada, posicion + 1, *it, buffer, aceptada);
            buffer.erase(buffer.size() - tmp.size(), tmp.size());
        }
        buffer.erase(buffer.size() - 3, 3);
    }

    if(camino_incompleto)
    {
        buffer += "\t\t";
        buffer += entrada.at(posicion);
        buffer += "\t\t";
        buffer += 'X';
        analizar_cadena(entrada, entrada.size(), estado_t(id_invalido), buffer, aceptada);
    }

}


void NFA::estados_muerte() const
{
    std::string buffer;

    for (const auto& i: get_Q())
    {
        if(i.es_muerte())
        {
            buffer += std::to_string(i.get_id());
            buffer += ", ";
        }
    }

    if(!buffer.empty())
    {
        buffer.erase(buffer.size() - 2, 2);
        std::cout << "El Automata Contiene Estados de Muerte" << std::endl;
        std::cout << "\tEstados de muerte: " << "{" << buffer << "}" << std::endl;
    }

    else

        std::cout << "El Automata No Contiene Estados de Muerte" << std::endl;
}

void NFA::estados_importantes() const
{
    std::string importante;
    std::string no_importante;

    for (const auto& i: get_Q())
    {
        if(i.es_importante())
        {
            importante += std::to_string(i.get_id());
            importante += ", ";
        }
        else
        {
            no_importante += std::to_string(i.get_id());
            no_importante += ", ";
        }
    }

    if (!importante.empty())    importante.erase(importante.size() - 2, 2);

    if(!no_importante.empty())  no_importante.erase(no_importante.size() - 2, 2);

    std::cout << "Estados Importantes: " << "{" << importante << "}" << std::endl;
    std::cout << "Estados No Importantes: " << "{" << no_importante << "}" << std::endl;
}


const std::set<estado_t> NFA::delta(estado_t& s, char entrada) const
{
    std::set<estado_t> tmp;

    for(const auto& i: s.get_transiciones(entrada))
        tmp.insert(*get_Q().find(i));

    return epsilon_clausura(tmp);
}

std::set<estado_t> NFA::epsilon_clausura(std::set<estado_t>& inicial) const
{

    std::set<estado_t> clausura = inicial;
    std::stack<estado_t> pila;

    for(const auto& i: clausura)
    {
        pila.push(i);
    }

    while (!pila.empty())
    {
        estado_t q = pila.top();
        pila.pop();
        const std::set<unsigned int>& transiciones = q.get_transiciones(epsilon);
        for(const auto& i: transiciones)
        {
            const estado_t destino = *get_Q().find(i);
            if (clausura.count(destino) == 0)
            {
                clausura.insert(destino);
                pila.push(destino);
            }
        }
    }

    return clausura;
}

void NFA::check_dfa()
{
    bool dfa = true;

    for(auto it = get_Q().begin(); it != get_Q().end() && dfa; ++it)
    {
        if (it->get_delta().size() != get_sigma().size())
            dfa = false;
    }

    set_dfa(dfa);
}

void NFA::mostrar_traza(std::ostream& os, const std::string& buffer) const
{
    os << '\n' << "Camino " << ++contador << '\n';

    os << "Estado Actual" << "\tEntrada" << "\t\tEstado Siguiente";

    os << buffer << '\n';
}

void NFA::reset()
{
    sigma_.clear();
    Q_.clear();
    F_.clear();
}


std::ostream& operator<<(std::ostream& os, const NFA& a)
{
    a.write(os);

    return os;
}

std::ifstream& operator>>(std::ifstream& is, NFA& a)
{
    a.read(is);

    return is;
}

}
