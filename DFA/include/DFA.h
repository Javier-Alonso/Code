/**
 * @class DFA
 *
 * @brief Automata Finito Determinista
 *
 * @details Esta clase simula un automata finito determinista.
 * Los datos se cargan desde fichero con un formato definido previamente.
 *
 * @note Soporta automatas no definidos completamente.
 *
 * @author Javier Alonso Delgado
 *
 * @date 2018/12/11
 *
*/

#ifndef DFA_H
#define DFA_H

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <set>
#include <string>

#include "estado_t.h"
#include "cadena_t.h"

namespace CyA
{
    static unsigned int contador;
    using alfabeto_t = std::set<char>;

    class DFA
    {
    private:

        alfabeto_t sigma_;          /**< Alfabeto de entrada. */
        std::set<estado_t> Q_;      /**< Conjunto de estados del automata. */
        std::set<estado_t> F_;      /**< Conjunto de estados de aceptacion del automata. */
        estado_t arranque_;         /**< Estado de arranque del automata. */

    public:

        /**
         * @brief Constructor por defecto
         */
        DFA() = default;
        /**
         * @brief Destructor
         */
        ~DFA() = default;
        /**
         * @brief Constructor de copia
         * @param Objeto de la misma clase
         */
        DFA(const DFA& other) = default;
        /**
         * @brief Sobrecarga del operador asignacion
         * @param Objeto de la misma clase
         * @return Objeto DFA copiado
         */
        DFA& operator=(const DFA& other);

        /**
         * @brief Muestra el automata
         * @details Permite escribir tanto por pantalla como a fichero
         * @param Flujo de salida
         * @return Flujo de salida
         */
        std::ostream& write(std::ostream& os) const;
        /**
         * @brief Lee el automata desde fichero
         * @param Flujo de entrada desde fichero
         * @return Flujo de entrada desde fichero
         */
        std::ifstream& read(std::ifstream& is);

        /**
        * @brief Pregunta por la cadena de entrada y la analiza
         * @details Usando la funcion de transicion, realiza una
         * traza por los estados del automata e indica si dicha
         * cadena es reconocida por el automata.
        * @note Comprueba si la cadena de entrada es valida
         * @see delta
        */
        void analizar_cadena();
        /**
         * @brief Muestra los estados de muerte del automata
         * @note Los estados de muerte han sido asignados en la lectura
         * desde fichero.
         */
        void estados_muerte() const;
        /**
         * @brief Minimiza el DFA, si es posible, y lo actualiza.
         * @details Mediante el algoritmo de construccion de subconjuntos,
         * va realizando una traza mostrando las particiones con cada simbolo del
         * alfabeto. Finalmente, actualiza los estados del automata.
         * @see nueva_particion
         * @see descomponer
         * @see particion
         */
        void minimizar();

        /**
         * @brief Funcion de Transicion
         * @param s -> estado de entrada
         * @param entrada -> simbolo del alfabeto con el que transitar
         * @return estado destino
         * @note Se comprueba si existe transicion con el simbolo dado. En
         * caso negativo, devuelve un estado invalido que se muestra en la
         * traza con el simbolo 'X'
         */
        estado_t delta(const estado_t& s, char entrada) const;

        /**
         * @brief Comprueba si el DFA es valido o no
         * @details Si un estado tiene dos o mas transiciones con el mismo simbolo,
         * el DFA introducido no es valido, indicando dicho error por pantalla.
         * @param s -> string que contiene los simbolos de transicion de un estado
         * @return Indica si es valido
         */
        bool invalido(std::string s) const;
        /**
         * @brief Indica si el automata esta definido o no
         * @details Se usa para no ejecutar metodos sin haber
         * leido el automata previamente desde fichero
         * @return Indica si esta definido o no
         */
        bool no_definido() const            { return Q_.empty(); }

        const alfabeto_t& get_sigma()     const { return sigma_; }
        const std::set<estado_t>& get_Q() const { return Q_; }
        const std::set<estado_t>& get_F() const { return F_; }
        const estado_t& get_arranque()    const { return *Q_.find(arranque_); }

    private:

        /**
         * @brief Reinicia la simulacion cuando se lee un nuevo fichero
         * @note Solo ocurre si hay definido un automata previo
         */
        void reset();
        /**
         * @brief Actualiza los conjuntos de estados del automata
         * @param PI -> subconjunto final obtenido al minimizar
         * @see actualizar_arranque
         * @see actualizar_transiciones
         */
        void actualizar(const std::set<std::set<estado_t>>& PI);
        void actualizar_arranque(const std::set<CyA::estado_t>& compatibles, bool& arranque_actualizado);
        void actualizar_transiciones(const std::set<std::set<estado_t>>& PI, estado_t& q, const char& simbolo) const;

        std::set<std::set<estado_t>> nueva_particion(const std::set<std::set<estado_t>>& PI_viejo) const;
        std::set<std::set<estado_t>> descomponer(const std::set<estado_t>& G, const std::set<std::set<estado_t>>& PI, const std::set<std::set<estado_t>>& modificacion) const;
        std::set<std::set<estado_t>> particion(const std::set<estado_t>& G, char a, const std::set<std::set<estado_t>>& PI) const;

        void set_sigma(const alfabeto_t& val)     { sigma_ = val; }
        void set_Q(const std::set<estado_t>& val) { Q_ = val; }
        void set_F(const std::set<estado_t>& val) { F_ = val; }
        void set_arranque(const estado_t& val)    { arranque_ = val; }



    };

std::ostream& operator<<(std::ostream& os, const DFA& a);
std::ifstream& operator>>(std::ifstream& is, DFA& a);

std::ostream& operator<<(std::ostream& os, const std::set<estado_t>& obj);
std::ostream& operator<<(std::ostream& os, const std::set<std::set<estado_t>>& obj);

}

#endif // DFA_H
