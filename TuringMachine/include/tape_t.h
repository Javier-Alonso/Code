/**
 *
 * @class CyA::tape_t
 * @brief Cinta de la Maquina de Turing
 *
 * @details Esta clase representa la cinta de entrada de una maquina de Turing.
 * Dicha cinta es cargada desde fichero.
 *
 * @note El simbolo blanco se representa por el simbolo '$'.
 *
 * @author Javier Alonso Delgado
 *
 * @date 2019/01/03
 *
*/

#ifndef TAPE_T_H
#define TAPE_T_H

#include <deque>
#include <fstream>
#include <iostream>

namespace CyA
{

const char simbolo_blanco = '$';

class tape_t
{
    private:

        std::deque<char> cadena_;   /**< Contenedor de los caracteres de la cinta. **/
        size_t posicion_ = 0;       /**< Posicion del cabezal en la cinta. **/

    public:

        /**
         * @brief Constructor por defecto
         */
        tape_t() = default;
        /**
         * @brief Destructor por defecto
         */
        ~tape_t() = default;
        /**
         * @brief Constructor de copia
         * @param other -> objeto de la misma clase
         */
        tape_t(const tape_t& other) = default;

        /**
         * @brief Lee la cinta desde fichero
         * @param is -> flujo de entrada
         * @return flujo de entrada
         */
        std::ifstream& read(std::ifstream& is);
        /**
         * @brief Escribe la parte a la derecha del cabezal de la cinta
         * @param os -> flujo de salida
         * @return flujo de salida
         */
        std::ostream& write_rhs(std::ostream& os) const;
        /**
         * @brief Escribe la parte a la izquierda del cabezal de la cinta
         * @param os -> flujo de salida
         * @return flujo de salida
         */
        std::ostream& write_lhs(std::ostream& os) const;
        /**
         * @brief Devuelve el caracter sobre el que esta el cabezal
         * @return caracter actual
         */
        char get_simbolo() const             { return cadena_.at(posicion_); }
        /**
         * @brief Escribe un simbolo en la posicion actual del cabezal
         * @param simbolo -> caracter a escribir
         */
        void escribir_simbolo(char simbolo)  { cadena_.at(posicion_) = simbolo; }
        /**
         * @brief Desplaza el cabezal por la cinta
         * @note Para simular que es infinita, si la posicion sobrepasa los
         * limites del contenedor, se escribe un simbolo blanco donde corresponda.
         * @param direccion -> R(derecha) o L(izquierda)
         * @see insertar_blanco
         */
        void desplazar(char direccion);

    private:
        /**
         * @brief Metodo auxiliar para escribir un simbolo blanco
         * @param direccion -> R(derecha) o L(izquierda)
         */
        void insertar_blanco(char direccion);

};

std::ifstream& operator>>(std::ifstream& is, tape_t& rhs);

}

#endif // TAPE_T_H
