/**
 *
 * @class CyA::GR_t
 * @brief Gramatica Independiente del Contexto
 *
 * @details Esta clase representa una gramatica independiente del contexto.
 * Dicha gramatica es cargada desde fichero, puede ser simplificada y exportada.
 * El formato de exportacion es el siguiente:
 *
 *      Numero de simbolos terminales
 *      Simbolos terminales
 *      Numero de simbolos no terminales
 *      Simbolos no terminales
 *      Lista de reglas de produccion
 *
 * @note El simbolo de arranque se corresponde con el primer simbolo no terminal del fichero.
 * @note La cadena vacia es denotada por el caracter '~'.
 * @note Los simbolos de la gramatica son representados por un unico caracter.
 *
 * @author Javier Alonso Delgado
 *
 * @date 2018/12/28
 *
*/

#ifndef GR_T_H
#define GR_T_H

#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <utility>
#include <vector>


namespace CyA
{

using produccion_t = std::map<char, std::vector<std::string>>;          /**< Contenedor para las producciones. */

class GR_t
{
    private:

        char arranque_ = 'S';              /**< Simbolo de arranque de la gramatica. */
        std::set<char> terminales_;        /**< Conjunto de terminales de la gramatica. */
        std::set<char> noterminales_;      /**< Conjunto de no terminales de la gramatica. */
        produccion_t producciones_;        /**< Reglas de produccion para la gramatica. */

    public:

        /**
         * @brief Constructor por defecto
         */
        GR_t() = default;
        /**
         * @brief Destructor por defecto
         */
        ~GR_t() = default;
        /**
         * @brief Constructor de copia
         * @param other -> objeto de la misma clase
         */
        GR_t(const GR_t& other) = default;
        /**
        * @brief Lee la gramatica desde fichero
        * @param Flujo de entrada desde fichero
        * @return Flujo de entrada desde fichero
        */
        std::istream& read(std::istream& is);
        /**
         * @brief Muestra la gramatica generada
         * @details Permite escribir tanto por pantalla como a fichero
         * @param os -> Flujo de salida
         * @return Flujo de salida
         */
        std::ostream& write(std::ostream& os) const;
        /**
         * @brief Simplifica la gramatica actual
         * @details Utiliza el algoritmo de eliminacion de las
         * producciones vacias y, posteriormente, el de eliminacion
         * de las producciones unitarias.
         * @note El metodo ordena las producciones una vez simplificadas
         * @see eliminar_unitarias
         * @see eliminar_vacias
         */
        void simplificar();

    private:

        /**
         * @brief Metodo auxiliar para saber si un simbolo es no terminal
         * @param simbolo -> caracter a examinar
         * @return verdadero o falso, segun corresponda
         */
        bool es_noterminal(char simbolo) const;
        /**
         * @brief Metodo auxiliar para saber si un simbolo es unitario
         * @param regla -> regla de produccion a examinar
         * @return verdadero o falso, segun corresponda
         */
        bool es_unitario(const std::string& regla) const;
        /**
         * @brief Comprueba si la cadena vacia pertenece al lenguaje generado por la gramatica
         * @details Utilizando el conjunto de variables anulables ya calculado, comprueba si el
         * simbolo de arranque es anulable. En caso afirmativo, la cadena vacia pertenece a dicho lenguaje.
         * @param anulables -> conjunto con las variables anulables de la gramatica
         * @return verdadero o falso, segun corresponda
         */
        bool epsilon_pertenece(const std::set<char>& anulables) const;
        /**
         * @brief Elimina las producciones vacias
         * @details Utiliza un metodo auxiliar para
         * eliminar las producciones vacias de la gramatica y
         * luego ajusta las reglas de produccion que sean necesarias.
         * @see calcular_anulables
         */
        void eliminar_vacias();
        /**
         * @brief Elimina las producciones unitarias
         * @details Analiza las producciones de la gramatica en busca
         * de reglas de produccion unitarias. En caso afirmativo, las elimina
         * utilizando un algoritmo basado en busqueda por pares.
         * @see calcular_unitarias
         */
        void eliminar_unitarias();

        /**
         * @brief Calcula las variables anulables de la gramatica
         * @note Este metodo elimina las producciones vacias segun las encuentra.
         * @param H -> conjunto para almacenar las variables anulables
         */
        void calcular_anulables(std::set<char>& H);
        /**
         * @brief Calcula las variables unitarias de la gramatica
         * @param H -> conjunto para almacenar los pares de variables unitarias
         */
        void calcular_unitarias(std::set<std::pair<char, char>>& H) const;


};

std::ostream& operator<<(std::ostream& os, const GR_t& rhs);
std::istream& operator>>(std::istream& is, GR_t& rhs);

std::vector<std::string> split(std::string str, const std::string& token);

}

#endif  //GR_T_H