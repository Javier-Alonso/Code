/**
 *
 * @class CyA::TuringMachine
 * @brief Maquina de Turing
 *
 * @details Esta clase representa una maquina de Turing.
 * Dicha maquina es cargada desde fichero. Permite mostrar la maquina y analizar cintas.
 * El formato del fichero es el siguiente:
 *
 *      Numero de estados de la maquina
 *      Estado de arranque
 *      Estados de aceptacion
 *      Numero de t-uplas
 *      Lista de t-uplas
 *
 * @note Los simbolos del alfabeto de la cinta puedes ser digitos o letras.
 * @note Los estados son enteros que comienzan con el estado inicial igual a cero.
 * @note El simbolo blanco se representa por el simbolo '$'.
 *
 * @author Javier Alonso Delgado
 *
 * @date 2019/01/03
 *
*/

#ifndef TURINGMACHINE_H
#define TURINGMACHINE_H

#define MAX_IT 100

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "tape_t.h"
#include "tuple_t.h"

namespace CyA
{


class TuringMachine
{
    private:

        unsigned int arranque_ = 0;     /**< Estado de arranque de la maquina. */
        std::set<unsigned int> Q_;      /**< Conjunto de estados de la maquina. */
        std::set<unsigned int> F_;      /**< Conjunto de estados de aceptacion. */
        std::vector<tuple_t> tuplas_;   /**< T-uplas de cada estado de la maquina. */

    public:

        /**
         * @brief Constructor por defecto
         */
        TuringMachine() = default;
        /**
         * @brief Destructor por defecto
         */
        ~TuringMachine() = default;
        /**
         * @brief Constructor de copia
         * @param other -> objeto de la misma clase
         */
        TuringMachine(const TuringMachine& other) = default;
        /**
        * @brief Lee la maquina desde fichero
        * @param is -> Flujo de entrada desde fichero
        * @return Flujo de entrada desde fichero
        */
        std::ifstream& read(std::ifstream& is);
        /**
         * @brief Muestra la maquina
         * @details Permite escribir tanto por pantalla como a fichero
         * @param os -> Flujo de salida
         * @return Flujo de salida
         */
        std::ostream& write(std::ostream& os) const;
        /**
         * @brief Analiza una cinta de entrada
         * @details Examina el simbolo sobre el que se encuentra el cabezal de la maquina.
         * A continuacion, busca una transicion con dicho simbolo: en caso afirmativo, escribe
         * y desplaza la cinta, actualizando el estado actual. En caso contrario, la maquina para
         * y acepta/rechaza la cadena analizada.
         * @param cinta -> cinta a analizar
         * @see transicion_definida
         * @see mostrar_transicion
         * @see transitar
         */
        void analizar_cinta(tape_t cinta) const;

    private:

        /**
         * @brief Busca transiciones validas para un estado y simbolo dados
         * @note Este metodo actualiza la tupla actual utilizada por el metodo
         * para analizar la cinta.
         * @param estado -> estado actual
         * @param simbolo -> simbolo de entrada de la cadena
         * @param tupla_actual -> actualiza a la tupla del estado destino (si existe la transicion)
         * @return verdadero o falso, segun corresponda
         */
        bool transicion_definida(unsigned int estado, char simbolo, tuple_t& tupla_actual) const;
        /**
         * @brief Metodo auxiliar para mostrar cada transicion de la traza
         * @param cinta -> cinta actual
         * @param estado_actual -> estado donde se encuentra la maquina
         */
        void mostrar_transicion(const tape_t &cinta, unsigned int estado_actual) const;
        /**
         * @brief Transita la maquina de Turing al estado correspondiente
         * @param cinta -> cinta a ser escrita
         * @param tupla -> tupla actual
         * @param estado -> estado de destino
         */
        void transitar(tape_t &cinta, const tuple_t &tupla, unsigned int &estado) const;
        /**
         * @brief Metodo auxiliar que comprueba si un estado es de aceptacion
         * @param estado_actual -> estado a analizar
         * @return verdadero o falso, segun corresponda
         */
        bool es_aceptacion(unsigned int estado_actual) const;
};

std::ostream& operator<<(std::ostream& os, const TuringMachine& rhs);
std::ifstream& operator>>(std::ifstream& is, TuringMachine& rhs);

}

#endif  //TURINGMACHINE_H