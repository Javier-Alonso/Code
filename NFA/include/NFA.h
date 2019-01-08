/**
 * @class NFA
 *
 *
 * @brief Automata Finito No Determinista
 *
 * @details Esta clase simula un automata finito no determinista con o
 * sin epsilon-transiciones. Soporta automatas no definidos
 * completamente. Los datos se cargan desde fichero con un
 * formato definido previamente.
 *
 * @note Los bucles infitos de epsilon deben ser controlados por el usuario
 *
 * @author Javier Alonso Delgado
 *
 * @date 2018/12/04
 *
 *
*/

#ifndef NFA_H
#define NFA_H

#include <fstream>
#include <iomanip>
#include <iostream>
#include <set>
#include <stack>
#include <string>

#include "estado_t.h"
#include "cadena_t.h"

namespace CyA
{

using alfabeto_t = std::set<char>;
static unsigned int contador = 0;

class NFA
{
    private:

        alfabeto_t sigma_;      /**< Alfabeto de entrada. */
        bool esDFA_ = false;    /**< Indica si el automata cargado es un DFA o no. */
        std::set<estado_t> Q_;  /**< Conjunto de estados del automata. */
        std::set<estado_t> F_;  /**< Conjunto de estados de aceptacion. */
        estado_t arranque_;     /**< Estado de arranque del automata. */

    public:

        /**
         * @brief Constructor por defecto
         */
        NFA() = default;

        /**
         * @brief Destructor
         */
        ~NFA() = default;

        /**
         * @brief Constructor de copia
         * @param Objeto de la misma clase
         */
        NFA(const NFA& other) = default;

        /**
         * @brief Sobrecarga del operador asignacion
         * @param Objeto de la misma clase
         * @return Objeto NFA copiado
         */
        NFA& operator=(const NFA& other);

        /**
         * @brief Muestra el automata por la salida estandar
         * @param os
         * @return os
         */
        std::ostream& write(std::ostream& os) const;
        /**
         * @brief Lee el automata desde fichero
         * @param is
         * @return ifstream
         */
        std::ifstream& read(std::ifstream& is);

        /**
         * @brief Obtiene la cadena a analizar
         * @note Analiza si la cadena es valida o no
         */
        void leer_cadena() const;
        /**
         * @brief Analiza la cadena de entrada
         * @param cadena_t -> cadena a analizar
         * @param size_t -> posicion del caracter que se va a consumir
         * @param estado_t -> estado actual a ser evaluado
         * @param string -> buffer que acumula la traza realizada para cada camino
         * @param bool -> indica si el camino ha sido aceptado o no
         * @details Va generando todos los caminos posibles de forma recursiva utilizando
         * un algoritmo de busqueda en profundidad (DFS). Cuando un camino ha terminado, se
         * imprime cada traza utilizando una funcion auxiliar.
         * @see mostrar_traza
         */
        void analizar_cadena(const cadena_t&, size_t, const estado_t&, std::string, bool&) const;
        /**
         * @brief Muestra los estados de muerte del automata
         */
        void estados_muerte() const;
        /**
         * @Muestra los estados importantes y no importantes del automata
         */
        void estados_importantes() const;

        /**
         * @brief Halla la epsilon clausura de un conjunto de estados
         * @param inicial -> conjunto de estados a ser calculado
         * @return epsilon clausura
         */
        std::set<estado_t> epsilon_clausura(std::set<estado_t>& inicial) const;
        /**
         * @brief Fucion de Transicion Extendida
         * @param s -> estado inicial
         * @param entrada -> simbolo de la cadena
         * @return conjunto de estados destino
         */
        const std::set<estado_t> delta(estado_t& s, char entrada)   const;
        /**
         * @brief Indica si el automata esta definido o no
         * @details Se usa para no ejecutar metodos sin haber
         * leido el automata previamente desde fichero
         * @return bool
         */
        bool definido()                   const { return !Q_.empty(); }

        bool  es_dfa()                    const { return esDFA_; }
        const alfabeto_t& get_sigma()     const { return sigma_; }
        const std::set<estado_t>& get_Q() const { return Q_; }
        const std::set<estado_t>& get_F() const { return F_; }
        const estado_t& get_arranque()    const { return *Q_.find(arranque_); }

    private:

        /**
         * @brief Comprueba si el automata introducido es un DFA
         * @details Se comprueba mirando si, para algun estado, el
         * numero de transiciones es distinto del numero de simbolos
         * del alfabeto, lo cual indicaria que hay alguna transicion
         * con epsilon o varias con el mismo simbolo del alfabeto.
         */
        void check_dfa();

        /**
         * @brief Muestra la traza para un camino dado
         * @param os -> Flujo de salida
         * @param buffer -> String que contiene la traza de un camino
         */
        void mostrar_traza(std::ostream& os, const std::string& buffer) const;
        /**
         * @brief Reinicia la simulacion cuando se lee un nuevo fichero
         * @note Solo ocurre si hay definido un automata previo
         */
        void reset();

        void set_sigma(const alfabeto_t& val)     { sigma_ = val; }
        void set_dfa(bool val)                    { esDFA_ = val; }
        void set_Q(const std::set<estado_t>& val) { Q_ = val; }
        void set_F(const std::set<estado_t>& val) { F_ = val; }
        void set_arranque(const estado_t& val)    { arranque_ = val; }

};

std::ostream& operator<<(std::ostream& os, const NFA& a);
std::ifstream& operator>>(std::ifstream& is, NFA& a);

}

#endif // NFA_H
