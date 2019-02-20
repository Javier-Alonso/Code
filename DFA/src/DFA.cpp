#include "DFA.h"

namespace CyA {

    DFA &DFA::operator=(const DFA &rhs) {
        if (this == &rhs) return *this;

        set_arranque(rhs.get_arranque());
        set_F(rhs.get_F());
        set_Q(rhs.get_Q());
        set_sigma(rhs.get_sigma());

        return *this;
    }


    std::ostream &DFA::write(std::ostream &os) const {
        os << get_Q().size() << std::endl;

        os << get_arranque() << std::endl;

        for (const auto &i: get_Q()) {
            os << i.get_id() << " " << i.es_aceptacion() << " " << i.get_delta().size() << " ";
            for (const auto &j: i.get_delta())
                os << j << " ";
            os << std::endl;
        }

        return os;
    }


    std::ifstream &DFA::read(std::ifstream &is) {
        if (!no_definido()) reset();

        std::string fichero;

        std::cout << "Introduce el nombre del fichero: ";
        std::cin >> fichero;

        is.open(fichero);

        if (is.is_open()) {
            unsigned int nestados;
            unsigned int init;

            is >> (unsigned int &) nestados >> (unsigned int &) init;
            set_arranque(init);

            bool aceptacion;
            bool muerte;
            char entrada;
            std::string check;
            unsigned int destino;
            unsigned int id;
            unsigned int ntransiciones;

            for (unsigned int i = 0; i < nestados; i++) {
                is >> (unsigned int &) id >> (bool &) aceptacion >> (unsigned int &) ntransiciones;

                estado_t temp(id, aceptacion);

                check.clear();

                muerte = true;

                for (unsigned int j = 0; j < ntransiciones; j++) {
                    is >> (char &) entrada >> (unsigned int &) destino;

                    check.push_back(entrada);

                    sigma_.insert(entrada);

                    temp.insert_transicion(entrada, destino);

                    if (id != destino || aceptacion) muerte = false;

                    temp.set_muerte(muerte);
                }

                if (invalido(check)) {
                    is.close();
                    std::cerr << "Error en la definicion del automata." << std::endl;
                    return is;
                }

                Q_.insert(temp);

                if (aceptacion) {
                    F_.insert(temp);
                }
            }

            is.close();
            std::cout << "Fichero leido correctamente." << std::endl;
        } else
            std::cerr << "Error en la apertura del fichero." << std::endl;

        return is;
    }


void DFA::analizar_cadena()
{

    bool aceptada = false;
    cadena_t s;
    estado_t q = get_arranque();

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

    std::cout << "Estado Actual" << "\tEntrada" << "\t\tEstado Siguiente" << std::endl;

    for(const auto& i: s)
    {
        std::cout << q << std::setw(16) << i;
        q = delta(q, i);
        if (q.get_id() == id_invalido)
        {
            std::cout << std::setw(16) << "X" << std::endl;
            break;
        }
        std::cout << std::setw(16) << q << std::endl;
    }

    auto destino = get_F().find(q);

    if (destino != get_F().end())

        aceptada = true;

    std::cout << "Cadena de entrada" << ((aceptada)? " " : " NO ") << "ACEPTADA" << std::endl;
}


void DFA::estados_muerte() const
{
    std::string buffer;

    for(const auto& i: get_Q())
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

estado_t DFA::delta(const estado_t& s, char entrada) const
{

    for(const auto& i: s.get_delta())
        if(i.get_simbolo() == entrada)
            return *get_Q().find(i.get_destino());

    return estado_t(id_invalido);
}


bool DFA::invalido(std::string s) const
{
    bool invalido = false;

    for(size_t i = 0; i < s.size() && !invalido; i++)
        for (size_t j = i + 1; j < s.size(); j++)
            if(s.at(i) == s.at(j))
                invalido = true;

    return invalido;
}

void DFA::reset()
{
    sigma_.clear();
    Q_.clear();
    F_.clear();
}


void DFA::minimizar()
{
    std::set<std::set<estado_t>> PI;
    std::set<std::set<estado_t>> PI_viejo;

    std::set<estado_t> temp;
    std::set_difference(Q_.begin(), Q_.end(), F_.begin(), F_.end(), std::inserter(temp, temp.begin()));
    PI.insert(temp);
    PI.insert(get_F());

    std::cout << "P0 = " << PI << "\n\n";

    contador = 0;

    while(PI != PI_viejo)
    {
        PI_viejo = PI;
        PI = nueva_particion(PI_viejo);
    }

    std::cout << "Conjunto de Particiones Final: " << PI << '\n';
    std::cout << "El DFA minimo tiene" << " " << PI.size() << " " << "estados." << std::endl;

    actualizar(PI);

}

void DFA::actualizar(const std::set<std::set<estado_t>>& PI)
{
    Q_.clear();
    F_.clear();

    bool arranque_actualizado = false;
    unsigned int id = 0;

    for(const auto& compatibles: PI)
    {
        estado_t representante = *compatibles.begin();

        if(!arranque_actualizado)
        {
            actualizar_arranque(compatibles, arranque_actualizado);
        }

        representante = id++;

        for(const auto& simbolo: get_sigma())
        {
            actualizar_transiciones(PI, representante, simbolo);
        }

        Q_.insert(representante);
    }

    for(const auto& q: get_Q())
    {
        if(q.es_aceptacion())
            F_.insert(q);
    }
}

void DFA::actualizar_arranque(const std::set<CyA::estado_t>& compatibles, bool& arranque_actualizado)
{
    for (const auto &p: compatibles)
        if (p == get_arranque())
        {
            set_arranque(p);
            arranque_actualizado = true;
        }
}

void DFA::actualizar_transiciones(const std::set<std::set<estado_t>>& PI, estado_t& q, const char& simbolo) const
{
    estado_t destino = q.get_transicion(simbolo);
    if(destino.get_id() != id_invalido)
    {
        unsigned int posicion = 0;
        for (const auto& conjunto: PI)
        {
            auto it = conjunto.find(destino);
            if(it != conjunto.end())
            {
                q.insert_transicion(simbolo, posicion);
            }
            posicion++;
        }
    }
}

std::set<std::set<estado_t>> DFA::nueva_particion(const std::set<std::set<estado_t>>& PI_viejo) const
{
    std::set<std::set<estado_t>> PI;
    std::set<std::set<estado_t>> descomposicion;

    for(const auto& G: PI_viejo)
    {
        descomposicion = descomponer(G, PI_viejo, PI);
        PI.insert(descomposicion.begin(), descomposicion.end());
    }

    return PI;
}

std::set<std::set<estado_t>> DFA::descomponer(const std::set<estado_t>& G, const std::set<std::set<estado_t>>& PI, const std::set<std::set<estado_t>>& modificacion) const
{
    std::set<std::set<estado_t>> T;
    std::set<std::set<estado_t>> traza;

    T.insert(G);

    for(const auto& a: get_sigma())
    {
        std::set<std::set<estado_t>> P;
        for(const auto& g: T)
        {
            const std::set<std::set<estado_t>> temp = particion(g, a, PI);
            P.insert(temp.begin(), temp.end());
        }
        T = P;

        traza.insert(modificacion.begin(), modificacion.end());
        traza.insert(T.begin(), T.end());
        traza.insert(++PI.find(G), PI.end());

        std::cout << "Con el simbolo" << " '" << a << "': \n";
        std::cout << "P" << ++contador << " = " <<  PI << "\n\n";
    }
    return T;
}

std::set<std::set<estado_t>> DFA::particion(const std::set<estado_t>& G, char a, const std::set<std::set<estado_t>>& PI) const
{
    std::set<std::set<estado_t>> T;
    std::set<estado_t> temp;

    for(const auto& H: PI)
    {
        temp.clear();
        for(const auto& q: G)
            if(H.count(delta(q, a)) == 1)
            {
                temp.insert(q);
            }
        if(!temp.empty())
            T.insert(temp);
    }
    return T;
}


std::ostream& operator<<(std::ostream& os, const DFA& a)
{
    a.write(os);

    return os;
}


std::ifstream& operator>>(std::ifstream& is, DFA& a)
{
    a.read(is);

    return is;
}

std::ostream& operator<<(std::ostream& os, const std::set<estado_t>& obj)
{
    os << '{';

    auto it = obj.cbegin();

    if (it != obj.cend())
    {
        os << *it++;
        while (it != obj.cend())
            os << ',' << *it++;
    }

    os << '}';

    return os;
}

std::ostream& operator<<(std::ostream& os, const std::set<std::set<estado_t>>& obj)
{
    os << '{';

    auto it = obj.cbegin();

    if (it != obj.cend())
    {
        os << *it++;
        while (it != obj.cend())
            os << ',' << *it++;
    }

    os << '}';

    return os;
}

}
