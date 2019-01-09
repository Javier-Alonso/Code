#include "GR_t.h"

namespace CyA
{

std::istream& GR_t::read(std::istream& is)
{

    char simbolo_actual;
    size_t nsimbolos;
    std::string linea;
    std::string produccion;
    std::vector<std::string> producciones;

    is >> (size_t &) nsimbolos;

    for(size_t i = 0; i < nsimbolos; i++)
    {
        is >> (char &) simbolo_actual;
        terminales_.insert(simbolo_actual);
    }

    is >> (size_t &) nsimbolos;

    is >> (char &) simbolo_actual;
    arranque_ = simbolo_actual;
    noterminales_.insert(simbolo_actual);

    for(size_t i = 1; i < nsimbolos; i++)
    {
        is >> (char &) simbolo_actual;
        noterminales_.insert(simbolo_actual);
    }

    for(size_t i = 0; i < noterminales_.size(); i++)
    {
        is >> (char &) simbolo_actual;
        is.ignore(256, '>');
        std::getline(is, linea);
        linea.erase(remove_if(linea.begin(), linea.end(), isspace), linea.end());
        producciones = split(linea, "|");
        producciones_.emplace(simbolo_actual, producciones);
    }

    return is;
}

std::ostream& GR_t::write(std::ostream& os) const
{

    os << terminales_.size() << std::endl;

    for(const auto& simbolo: terminales_)
    {
        os << simbolo << " ";
    }

    os << std::endl << noterminales_.size() << std::endl;

    os << arranque_ << " ";

    for(const auto& simbolo: noterminales_)
    {
        if(simbolo != arranque_)  os << simbolo << " ";
    }

    os << std::endl;

    auto it = producciones_.find(arranque_);
    if(it != producciones_.end())
    {
        os << it->first << " -> ";

        for(const auto& regla: it->second)
        {
            os << regla;

            if(regla != it->second.back())
            {
                os << " | ";
            }
        }

        os << std::endl;
    }

    for(const auto& produccion: producciones_)
    {
        if(produccion.first != arranque_)
        {
            os << produccion.first << " -> ";

            for(const auto& regla: produccion.second)
            {
                os << regla;

                if(regla != produccion.second.back())
                {
                    os << " | ";
                }
            }

            os << std::endl;
        }
    }

    return os;
}

void GR_t::simplificar()
{
    eliminar_vacias();
    eliminar_unitarias();

    for(auto& produccion: producciones_)
    {
        std::sort(produccion.second.begin(), produccion.second.end());
    }
}

bool GR_t::es_noterminal(char simbolo) const
{
    return noterminales_.count(simbolo) == 1;
}

bool GR_t::es_unitario(const std::string& regla) const
{
    return (regla.size() == 1 && es_noterminal(regla.front()));
}

bool GR_t::epsilon_pertenece(const std::set<char>& anulables) const
{
    return (anulables.count(arranque_) == 1);
}

void GR_t::eliminar_vacias()
{
    std::set<char> anulables;
    calcular_anulables(anulables);

    bool incluir_epsilon = epsilon_pertenece(anulables);

    for(auto& A: producciones_)
    {
        for(size_t i = 0; i < A.second.size(); i++)
        {
            const std::string regla_actual = A.second.at(i);
            for(size_t j = 0; j < regla_actual.size(); j++)
            {
                if(anulables.count(regla_actual.at(j)) != 0)
                {
                    std::string nueva_regla = regla_actual;
                    nueva_regla.erase(j, 1);
                    if(!nueva_regla.empty() && std::find(A.second.begin(), A.second.end(), nueva_regla) == A.second.end())
                    {
                        A.second.push_back(nueva_regla);
                    }
                }
            }
        }
    }

    if(incluir_epsilon)
    {
        auto arranque_it = producciones_.find(arranque_);
        arranque_it->second.emplace_back("~");
    }
}

void GR_t::calcular_anulables(std::set<char>& H)
{
    std::set<char> H_viejo;

    for(auto& A: producciones_)
    {
        for(auto it = A.second.begin(); it != A.second.end(); ++it)
        {
            if(*it == "~")
            {
                H.insert(A.first);
                A.second.erase(it, it + 1);
                break;
            }
        }
    }

    while(H != H_viejo)
    {
        H_viejo = H;

        for(const auto& B: producciones_)
        {
            for(const auto& regla: B.second)
            {
                bool anulable = true;

                for(const auto& simbolo: regla)
                {
                    if(H.count(simbolo) == 0)
                    {
                        anulable = false;
                        break;
                    }
                }
                if(anulable)
                {
                    H.insert(B.first);
                    break;
                }
            }
        }
    }
}

void GR_t::eliminar_unitarias()
{
    std::set<std::pair<char, char>> unitarias;
    calcular_unitarias(unitarias);

    for(auto& A: producciones_)
    {
        for(size_t i = 0; i < A.second.size(); i++)
        {
            if(es_unitario(A.second.at(i)))
            {
               A.second.erase(A.second.begin() + i);
            }
        }
    }

    for(auto& A: producciones_)
    {
        for(const auto& pareja: unitarias)
        {
            if(pareja.second == A.first)
            {
                auto it = producciones_.find(pareja.first);
                if(it != producciones_.end())
                {
                    for(const auto& regla: A.second)
                    {
                        if(std::find(it->second.begin(), it->second.end(), regla) == it->second.end())
                        {
                            it->second.push_back(regla);
                        }
                    }
                }
            }
        }
    }
}

void GR_t::calcular_unitarias(std::set<std::pair<char, char>>& H) const
{
    std::set<std::pair<char, char>> H_viejo;

    for(const auto& A: producciones_)
    {
        for(const auto& regla: A.second)
        {
            if(es_unitario(regla))
            {
                H.emplace(A.first, regla.front());
            }
        }
    }

    while(H != H_viejo)
    {
        H_viejo = H;

        for(const auto& pareja1: H)
        {
            for(const auto& pareja2: H)
            {
                if(pareja1.second == pareja2.first)
                {
                    const auto candidato = std::make_pair(pareja1.first, pareja2.second);
                    if(H.count(candidato) == 0)
                    {
                        H.insert(candidato);
                    }
                }
            }
        }
    }
}


std::ostream& operator<<(std::ostream& os, const GR_t& rhs)
{
    rhs.write(os);

    return os;
}

std::istream& operator>>(std::istream& is, GR_t& rhs)
{
    rhs.read(is);

    return is;
}


std::vector<std::string> split(std::string str, const std::string& token)
{
    std::vector<std::string> result;

    while(!str.empty())
    {
        auto index = str.find(token);
        if(index != std::string::npos)
        {
            result.push_back(str.substr(0, index));
            str = str.substr(index + token.size());
            if(str.empty())
            {
                result.push_back(str);
            }
        }
        else
        {
            result.push_back(str);
            str = "";
        }
    }

    return result;
}


}
