"""
ChemTech Codex integrates and solves general chemistry concepts.
Copyright (C) 2024  Raphael Panaligan

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Affero General Public License for more details.

You should have received a copy of the GNU Affero General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
"""

from functools import reduce
from math import e, fsum, log, log10
from os import path, remove
from textwrap import dedent

from prettytable import PrettyTable

# Defines the path to where the file containing the results would be created.
file_path = "results.txt"


def subscript(formula: str) -> str:
    """Converts all the integers in a string of a chemical formula into its subscript form.

    Args:
        formula (str): The string of a formula.

    Returns:
        str: The string of a chemical formula with subscripts.
    """
    # Create a translation dictionary for the integers and their subscript form.
    subscript_translation = str.maketrans("0123456789", "₀₁₂₃₄₅₆₇₈₉")

    # Separates the parts of the given chemical formula into its coefficient and main.
    coefficient = formula[0]
    main_formula = formula[1:]

    # Translates the integers in the main chemical formula into their subscript forms.
    main_formula = main_formula.translate(subscript_translation)

    # Returns the string of a chemical formula with subscripts.
    return coefficient + main_formula


def superscript(integers: str) -> str:
    """Converts all the integers in a string into its subscript form.

    Args:
        formula (str): The string.

    Returns:
        str: The string with subscripts.
    """
    # Create a translation dictionary for the integers and their superscript form.
    superscript_translation = str.maketrans("0123456789", "⁰¹²³⁴⁵⁶⁷⁸⁹")

    # Translates the integers into their superscript forms and returns it.
    return integers.translate(superscript_translation)


def calculate_thermochemistry(raw_chemical_equation: str) -> None:
    """Runs the thermodynamics calculator."""
    # Creates a new ASCII table to store the givens.
    givens_table = PrettyTable(["Formula", "Type", "Number", "Standard Heat (ΔH°f)", "Standard Entropy (S°)"])

    # Separates the chemical equation into its reactants and products.
    chemical_equation = raw_chemical_equation.replace(" ", "").split("->")
    # Formats and splits the reactants and products into individual formulas.
    reactants = list(map(subscript, chemical_equation[0].split("+")))
    products = list(map(subscript, chemical_equation[1].split("+")))
    # Rejoins the reactants and products into a stylized chemical equation.
    chemical_equation = " → ".join([" + ".join(reactants), " + ".join(products)])

    def get_thermodynamic_values(formulas: list[str], formula_type: str) -> tuple[list[float], list[float]]:
        """Gets the thermodynamic values of chemical formulas through inputs from the user.

        Args:
            formulas (list[str]): The chemical formulas.
            formula_type (str): The type of the thermodynamic values.

        Returns:
            tuple[list[float], list[float]]: The user given standard heats and entropies.
        """
        # Create lists to store the standard heats and entropies of the given formulas.
        standard_heats: list[float] = []
        standard_entropies: list[float] = []

        # Loop through each of the given chemical formulas.
        for formula in formulas:
            # Resets the variable to allow for looping if inputted value is invalid
            successful = False

            # Loops the input prompt until the user gives a valid thermodynamic value.
            while not successful:
                # Tries to prompt the user to input the thermodynamic values.
                try:
                    # Checks if a chemical formula has a coefficient.
                    if formula[0].isdigit():
                        # Separates the parts of the given chemical formula into its coefficient and main.
                        coefficient = int(formula[0])
                        main_formula = formula[1:]

                        # Asks the user for the standard heat value and multiplies it to the coefficient.
                        given_standard_heat = float(
                            input(f'\nPlease input the STANDARD HEAT (ΔH°f) of "{main_formula}" (float or int ONLY): ')
                        )
                        standard_heat = given_standard_heat * coefficient
                        # Asks the user for the standard entropy value and multiplies it to the coefficient.
                        given_standard_entropy = float(
                            input(f'Please input the STANDARD ENTROPY (S°) of "{main_formula}" (float or int ONLY): ')
                        )
                        standard_entropy = given_standard_entropy * coefficient

                        # Adds the given thermodynamic values to the table of givens
                        givens_table.add_row(  # type: ignore
                            [
                                main_formula,
                                formula_type,
                                coefficient,
                                f"{given_standard_heat} kJ/mol",
                                f"{given_standard_entropy} J/K × mol",
                            ]
                        )
                    else:
                        # Asks the user for the standard heat value.
                        standard_heat = given_standard_heat = float(
                            input(f'\nPlease input the STANDARD HEAT (ΔH°f) of "{formula}" (float or int ONLY): ')
                        )
                        # Asks the user for the standard entropy value.
                        standard_entropy = given_standard_entropy = float(
                            input(f'Please input the STANDARD ENTROPY (S°) of "{formula}" (float or int ONLY): ')
                        )

                        # Adds the given thermodynamic values to the table of givens
                        givens_table.add_row(  # type: ignore
                            [
                                formula,
                                formula_type,
                                1,
                                f"{given_standard_heat} kJ/mol",
                                f"{given_standard_entropy} J/K × mol",
                            ]
                        )

                    # Adds the given standard heat and entropy to the lists that will be returned by the function
                    standard_heats.append(standard_heat)
                    standard_entropies.append(standard_entropy)

                    # Stops the input prompt from repeating.
                    successful = True
                # Catches error exception for when the given value is invalid.
                except ValueError:
                    # Informs the user what values are valid.
                    print("\nThe given thermodynamic value must be a valid float or int ONLY.")

                    # Repeats the input prompt.
                    successful = False

        # Returns the lists of given standard heat and entropy values.
        return standard_heats, standard_entropies

    def calculate_rxn_enthalpy(
        product_standard_heats: list[float],
        reactant_standard_heats: list[float],
    ) -> float:
        """Calculates the standard enthalpy of the standard heats of the products and reactants.

        Args:
            product_standard_heats (list[float]): The standard heats of the products.
            reactant_standard_heats (list[float]): The standard heats of the reactants.

        Returns:
            float: The calculated standard enthalpy.
        """
        # Opens the file where the results are contained.
        file = open(file_path, "a", encoding="utf-8")

        # Writes to the file the equation that will be used to calculate the standard enthalpy.
        file.write("\n\nEquation for standard enthalpy (ΔH°rxn):\nΔH°rxn = Σ(nΔS° products) - Σ(nΔS° reactants)")

        # Writes to the file the solution for calculating the standard enthalpy.
        file.write(f'\n\nSolution for the standard enthalpy (ΔH°rxn) of "{chemical_equation}":')
        file.write(
            f"\nΔH°rxn = ({' + '.join(map(str, product_standard_heats))}) - ({' + '.join(map(str, reactant_standard_heats))}) kJ/mol"
        )

        # Calculates the standard enthalpy.
        standard_enthalpy = fsum(product_standard_heats) - fsum(reactant_standard_heats)

        # Writes to the file the calculated standard enthalpy.
        file.write(f"\nΔH°rxn = {standard_enthalpy} kJ/mol")

        # Checks if the enthalpy is greater than zero then writes to the file that the reaction is endothermic.
        if standard_enthalpy > 0:
            file.write(
                "\n\nBecause the standard enthalpy (ΔH°rxn) is greater than 0, the reaction must be ENDOTHERMIC."
            )
        # Checks if the enthalpy is less than zero then writes to the file that the reaction is exothermic.
        elif standard_enthalpy < 0:
            file.write("\n\nBecause the standard enthalpy (ΔH°rxn) is less than 0, the reaction must be EXOTHERMIC.")
        # Writes to the file that the reaction is neither endothermic or exothermic.
        else:
            file.write(
                "\n\nBecause the standard enthalpy (ΔH°rxn) is equal to 0, the reaction is neither endothermic or exothermic."
            )

        # Closes the opened file.
        file.close()

        # Returns the calculated standard enthalpy.
        return standard_enthalpy

    def calculate_rxn_entropy(
        product_standard_entropies: list[float],
        reactant_standard_entropies: list[float],
    ) -> float:
        """Calculates the standard entropy change of the standard entropies of the products and reactants.

        Args:
            product_standard_entropies (list[float]): The standard entropies of the products.
            reactant_standard_entropies (list[float]): The standard entropies of the reactants.

        Returns:
            float: The calculated standard entropy change.
        """
        # Opens the file where the results are contained.
        file = open(file_path, "a", encoding="utf-8")

        # Writes to the file the equation that will be used to calculate the standard entropy change.
        file.write(
            "\n\nEquation for standard entropy change / entropy of the system (ΔS°rxn / ΔS°sys):\nΔS°rxn = Σ(nΔH°f products) - Σ(nΔH°f reactants)"
        )

        # Writes to the file the solution for calculating the standard entropy change.
        file.write(
            f'\n\nSolution for the standard entropy change / entropy of the system (ΔS°rxn / ΔS°sys) of "{chemical_equation}":'
        )
        file.write(
            f"\nΔS°rxn = {' + '.join(map(str, product_standard_entropies))} - {' + '.join(map(str, reactant_standard_entropies))} J/K × mol"
        )

        # Calculates the standard entropy change.
        standard_entropy_change = fsum(product_standard_entropies) - fsum(reactant_standard_entropies)

        # Writes to the file the calculated standard entropy change.
        file.write(f"\nΔS°rxn = {standard_entropy_change} J/K × mol")

        # Closes the opened file.
        file.close()

        # Returns the calculated standard entropy change.
        return standard_entropy_change

    def calculate_surr_entropy(system_entropy: float, temperature: float) -> float:
        """Calculates the enthalpy of the surroundings of the system entropy and temperature.

        Args:
            system_entropy (list[float]): The system entropy or standard entropy change.
            temperature (list[float]): The temperature.

        Returns:
            float: The calculated entropy of the surroundings.
        """
        # Opens the file where the results are contained.
        file = open(file_path, "a", encoding="utf-8")

        # Writes to the file the equation that will be used to calculate the entropy of the surroundings.
        file.write("\n\nEquation for entropy of the surroundings (ΔS°surr):\nΔS°surr = -(ΔS°sys) / T")

        # Writes to the file the solution for calculating the entropy of the surroundings.
        file.write(
            f'\n\nSolution for the entropy of the surroundings (ΔS°surr) of "{chemical_equation} at {temperature} K":'
        )
        file.write(f"\nΔS°surr = -({system_entropy}) J/mol / {temperature} K")

        # Calculates the entropy of the surroundings.
        surrounding_entropy = (system_entropy * -1) / temperature

        # Writes to the file the calculated entropy of the surroundings.
        file.write(f"\nΔS°surr = {surrounding_entropy} J/K × mol")

        # Closes the opened file.
        file.close()

        # Returns the calculated entropy of the surroundings.
        return surrounding_entropy

    def calculate_univ_entropy(
        system_entropy: float,
        surrounding_entropy: float,
    ) -> float:
        """Calculates the entropy of the universe of the the system entropy and entropy of the surroundings.

        Args:
            system_entropy (list[float]): The system entropy or standard entropy change.
            surrounding_entropy (list[float]): The entropy of the surroundings.

        Returns:
            float: The calculated entropy of the universe.
        """
        # Opens the file where the results are contained.
        file = open(file_path, "a", encoding="utf-8")

        # Writes to the file the equation that will be used to calculate the entropy of the universe.
        file.write("\n\nEquation for entropy of the universe (ΔS°univ):\nΔS°univ = ΔS°sys ΔS°surr")

        # Writes to the file the solution for calculating the entropy of the universe.
        file.write(f'\n\nSolution for the entropy of the universe (ΔS°univ) of "{chemical_equation}":')
        file.write(f"\nΔS°univ = {system_entropy} J/K × mol + {surrounding_entropy} J/K × mol")

        # Calculates the entropy of the universe.
        universal_entropy = system_entropy + surrounding_entropy

        # Writes to the file the calculated entropy of the universe.
        file.write(f"\nΔS°univ = {universal_entropy} J/K × mol")

        # Checks if the enthalpy is greater than zero then writes to the file that the reaction is spontaneous.
        if universal_entropy > 0:
            file.write(
                "\n\nBecause the entropy of the universe (ΔS°univ) is greater than 0, the reaction must be SPONTANEOUS."
            )
        # Checks if the enthalpy is less than zero then writes to the file that the reaction is non-spontaneous.
        elif universal_entropy < 0:
            file.write(
                "\n\nBecause the entropy of the universe (ΔS°univ) is less than 0, the reaction must be NON-SPONTANEOUS."
            )
        # Writes to the file that the reaction is at equilibrium.
        else:
            file.write(
                "\n\nBecause the entropy of the universe (ΔS°univ) is equal to 0, the reaction is at equilibrium."
            )

        # Closes the opened file.
        file.close()

        # Returns the calculated entropy of the universe.
        return universal_entropy

    # Declares the default temperature value.
    temperature = 298.0

    # Resets the variable to allow for looping if inputted value is invalid
    successful = False

    # Loops the input prompt until the user gives a valid temperature value.
    while not successful:
        # Tries to prompt the user to input the temperature value.
        try:
            # Asks the user for the temperature that the chemical reaction occurs in.
            given_temperature = input(
                "Please input the temperature in Kelvins (float, int, or [press ENTER for 298] ONLY): "
            )

            # Checks if the user gave a temperature
            if not given_temperature == "":
                # Sets the temperature to the given temperature.
                temperature = float(given_temperature)

            # Stops the input prompt from repeating.
            successful = True
        # Catches error exception for when the given value is invalid.
        except ValueError:
            # Informs the user what values are valid.
            print("\nThe given temperature value must be a valid float or int ONLY.")

            # Repeats the input prompt.
            successful = False

    # Gets the thermodynamic values of the reactants and products.
    reactant_standard_heats, reactant_standard_entropies = get_thermodynamic_values(reactants, "Reactant")
    product_standard_heats, product_standard_entropies = get_thermodynamic_values(products, "Product")

    # Creates or opens a file to store where the results will be contained.
    file = open(file_path, "w+", encoding="utf-8")

    # Writes to the file the given chemical equation.
    file.write(f"The given chemical equation:\n{chemical_equation}")

    # Writes to the file the given temperature and the table of givens.
    file.write("\n\nGivens:")
    file.write(f"\nTemperature: {temperature} K")
    file.write("\n" + givens_table.get_string())  # type: ignore

    # Writes to the file the required values to be calculated.
    file.write("\n\nRequired:\nΔH°rxn, ΔS°rxn, and ΔS°univ")

    # Closes the created or opened file.
    file.close()

    # Calculates for the required values.
    standard_enthalpy = calculate_rxn_enthalpy(product_standard_heats, reactant_standard_heats)
    standard_entropy_change = calculate_rxn_entropy(product_standard_entropies, reactant_standard_entropies)
    surrounding_entropy = calculate_surr_entropy(
        standard_entropy_change,
        temperature,
    )
    universal_entropy = calculate_univ_entropy(standard_entropy_change, surrounding_entropy)

    # Opens the file where the results are contained.
    file = open(file_path, "a+", encoding="utf-8")

    # Writes to the file the final answers to the required values.
    file.write("\n\nThe FINAL ANSWERS:")
    file.write(f"\nΔH°rxn = {standard_enthalpy} J/K × mol")
    file.write(f"\nΔS°rxn = {standard_entropy_change} J/K × mol")
    file.write(f"\nΔS°univ = {universal_entropy} J/K × mol")

    # Closes the opened file.
    file.close()


def calculate_chemical_kinetics() -> None:
    """Runs the chemical kinetics calculator."""

    def calculate_concentration_after_time(
        temperature: float,
        rate_constant: float,
        initial_concentration: float,
        time: float,
    ) -> float:
        """Calculates the concentration after time.

        Args:
            temperature (float): The temperature.
            rate_constant (float): The rate constant.
            initial_concentration (float): The initial concentration.
            time (float): The time in seconds.

        Returns:
            float: The calculated concentration after time.
        """
        # Opens the file where the results are contained.
        file = open(file_path, "a", encoding="utf-8")

        # Writes to the file the equation that will be used to calculate the concentration after time.
        file.write(
            f"\n\nEquation for the concentration ([A]ₜ) after {time} seconds at {temperature} °C:\nln [A]ₜ = -kt + ln [A]₀"
        )

        # Writes to the file the solution for calculating the concentration after time.
        file.write(f"\n\nSolution for the concentration ([A]ₜ) after {time} seconds at {temperature} °C:")
        file.write(
            f"\nln [A]{subscript(str(round(time)))}ₛ = -({rate_constant} /s)({time} s) + ln ({initial_concentration} M)"
        )

        # Calculates the concentration after time.
        concentration_after_time = rate_constant * time
        concentration_after_time *= -1
        concentration_after_time += log(initial_concentration)
        concentration_after_time = e**concentration_after_time

        # Writes to the file the calculated concentration after time.
        file.write(f"\n[A]{subscript(str(round(time)))} = {concentration_after_time} M")

        # Closes the opened file.
        file.close()

        # Returns the calculated concentration after time.
        return concentration_after_time

    def calculate_time_of_concentration(
        temperature: float,
        rate_constant: float,
        initial_concentration: float,
        final_concentration: float,
    ) -> float:
        """Calculates the time to get a concentration.

        Args:
            temperature (float): The temperature.
            rate_constant (float): The rate constant.
            initial_concentration (float): The initial concentration.
            final_concentration (float): The final concentration.

        Returns:
            float: The calculated time to get a concentration.
        """
        # Opens the file where the results are contained.
        file = open(file_path, "a", encoding="utf-8")

        # Writes to the file the equation that will be used to calculate the time to get a concentration.
        file.write(f"\n\nEquation for the time (t) at {temperature} °C:\nln [A]ₜ / [A]₀ = -kt")

        # Writes to the file the solution for calculating the time to get a concentration.
        file.write(f"\n\nSolution for the time (t) at {temperature} °C:")
        file.write(f"\nln {final_concentration} M / {initial_concentration} M = -({rate_constant}t)")

        # Calculates the time to get a concentration.
        time_of_concentration = log(final_concentration / initial_concentration)
        rate_constant *= -1
        time_of_concentration /= rate_constant

        # Writes to the file the calculated time to get a concentration.
        file.write(f"\nt = {time_of_concentration} s")

        # Closes the opened file.
        file.close()

        # Returns the calculated time to get a concentration.
        return time_of_concentration

    def calculate_half_life_of_reaction(temperature: float, rate_constant: float) -> float:
        """Calculates the half-life of a reaction.

        Args:
            temperature (float): The temperature.
            rate_constant (float): The rate constant.

        Returns:
            float: The half-life of a reaction.
        """
        # Opens the file where the results are contained.
        file = open(file_path, "a", encoding="utf-8")

        # Writes to the file the equation that will be used to calculate the half-life of a reaction.
        file.write(f"\n\nEquation for the half-life (t1/2) at {temperature} °C:\nt1/2 = ln 2 / k")

        # Writes to the file the solution for calculating the half-life of a reaction.
        file.write(f"\n\nSolution for the time (t) at {temperature} °C:")
        file.write(f"\nt1/2 = ln 2 / {rate_constant}")

        # Calculates the half-life of a reaction.
        half_time_of_concentration = log(2) / rate_constant

        # Writes to the file the calculated half-life of a reaction.
        file.write(f"\nt1/2 = {half_time_of_concentration} s")

        # Closes the opened file.
        file.close()

        # Returns the calculated half-life of a reaction.
        return half_time_of_concentration

    # Resets the variable to allow for looping if inputted value is invalid
    successful = False

    # Loops the input prompt until the user gives valid temperature and rate constant values.
    while not successful:
        # Tries to prompt the user to input the time and rate constant values.
        try:
            # Asks the user for the temperature.
            given_temperature = float(input("\nPlease input the temperature in Celsius (float or int ONLY): "))

            # Asks the user for the rate constant.
            given_rate_constant = float(input("Please input the rate constant (float or int ONLY): "))

            # Stops the input prompt from repeating.
            successful = True
        # Catches error exception for when the given value is invalid.
        except ValueError:
            # Informs the user what values are valid.
            print("\nThe given temperature or rate constant value must be a valid float or int ONLY.")

            # Repeats the input prompt.
            successful = False

    # Resets the variable to allow for looping if inputted value is invalid
    successful = False

    # Loops the input prompt until the user gives a valid temperature value.
    while not successful:
        # Gives the user the instructions for providing the topic.
        print(
            dedent("""
            Please input the corresponding integer for the topic that you need this calculator for.
            1.) Determine the concentration of the reactant after a certain time elapsed?
            2.) Determine how much time has passed to get to a certain concentration of the reactant?
            3.) Determine the half-life of a reaction?
            """)
        )

        # Asks the user for the topic.
        given_topic = input("Topic: ")

        # Checks whether the given input is a "1" value.
        if given_topic == "1":
            try:
                # Asks the user for the initial concentration
                given_initial_concentration = float(
                    input("\nPlease input the initial concentration (float or int ONLY): ")
                )

                # Asks the user for the elapsed time.
                given_time = float(input("Please input the time in seconds (float or int ONLY): "))

                # Creates or opens a file to store where the results will be contained.
                file = open(file_path, "w+", encoding="utf-8")

                # Writes to the file the given temperature, rate constant, initial concentration, and time.
                file.write("Givens:")
                file.write(f"\nT = {given_temperature}")  # type: ignore
                file.write(f"\nk = {given_rate_constant}")  # type: ignore
                file.write(f"\n[A]₀ = {given_initial_concentration}")
                file.write(f"\nt = {given_time}")

                # Writes to the file the required values to be calculated.
                file.write("\n\nRequired:\n[A]ₜ")

                # Closes the created or opened file.
                file.close()

                # Calculates for the concentration after time.
                concentration_after_time = calculate_concentration_after_time(
                    given_temperature,  # type: ignore
                    given_rate_constant,  # type: ignore
                    given_initial_concentration,
                    given_time,
                )

                # Opens the file where the results are contained.
                file = open(file_path, "a+", encoding="utf-8")

                # Writes to the file the final answers to the required values.
                file.write("\n\nThe FINAL ANSWERS:")
                file.write(f"\n[A]{subscript(str(round(given_time)))} = {concentration_after_time} M")

                # Closes the opened file.
                file.close()

                # Stops the input prompt from repeating.
                successful = True
            # Catches error exception for when the given value is invalid.
            except ValueError:
                # Informs the user what values are valid.
                print("\nThe given time value must be a valid float or int ONLY.")

                # Repeats the input prompt.
                successful = False
        # Checks whether the given input is a "2" value.
        elif given_topic == "2":
            try:
                # Asks the user for the initial concentration
                given_initial_concentration = float(
                    input("\nPlease input the initial concentration (float or int ONLY): ")
                )

                # Asks the user for the final concentration
                given_final_concentration = float(input("Please input the final concentration (float or int ONLY): "))

                # Creates or opens a file to store where the results will be contained.
                file = open(file_path, "w+", encoding="utf-8")

                # Writes to the file the given temperature, rate constant, initial concentration, and final concentration.
                file.write("Givens:")
                file.write(f"\nT = {given_temperature}")  # type: ignore
                file.write(f"\nk = {given_rate_constant}")  # type: ignore
                file.write(f"\n[A]₀ = {given_initial_concentration}")
                file.write(f"\n[A]ₜ] = {given_final_concentration}")

                # Writes to the file the required values to be calculated.
                file.write("\n\nRequired:\nt")

                # Closes the created or opened file.
                file.close()

                # Calculates for the time to get a concentration.
                concentration_after_time = calculate_time_of_concentration(
                    given_temperature,  # type: ignore
                    given_rate_constant,  # type: ignore
                    given_initial_concentration,
                    given_final_concentration,
                )

                # Opens the file where the results are contained.
                file = open(file_path, "a+", encoding="utf-8")

                # Writes to the file the final answers to the required values.
                file.write("\n\nThe FINAL ANSWERS:")
                file.write(f"\nt = {concentration_after_time} s")

                # Closes the opened file.
                file.close()

                # Stops the input prompt from repeating.
                successful = True
            # Catches error exception for when the given value is invalid.
            except ValueError:
                # Informs the user what values are valid.
                print("\nThe given time value must be a valid float or int ONLY.")

                # Repeats the input prompt.
                successful = False
        # Checks whether the given input is a "3" value.
        elif given_topic == "3":
            # Creates or opens a file to store where the results will be contained.
            file = open(file_path, "w+", encoding="utf-8")

            # Writes to the file the given temperature, rate constant, initial concentration, and final concentration.
            file.write("Givens:")
            file.write(f"\nT = {given_temperature}")  # type: ignore
            file.write(f"\nk = {given_rate_constant}")  # type: ignore

            # Writes to the file the required values to be calculated.
            file.write("\n\nRequired:\nt")

            # Closes the created or opened file.
            file.close()

            # Calculates for the half-life of the reaction.
            half_time_of_concentration = calculate_half_life_of_reaction(
                given_temperature,  # type: ignore
                given_rate_constant,  # type: ignore
            )

            # Opens the file where the results are contained.
            file = open(file_path, "a+", encoding="utf-8")

            # Writes to the file the final answers to the required values.
            file.write("\n\nThe FINAL ANSWERS:")
            file.write(f"\nt1/2 = {half_time_of_concentration} s")

            # Closes the opened file.
            file.close()

            # Stops the input prompt from repeating.
            successful = True
        else:
            # Informs the user what values are valid.
            print('\nThe given value must be "1", "2", or "3" only.')

            # Repeats the input prompt.
            successful = False
            continue


def calculate_chemical_equilibrium(raw_chemical_equation: str) -> None:
    """Runs the chemical equilibrium calculator."""
    # Creates a new ASCII table to store the givens.
    givens_table = PrettyTable(["Formula", "Type", "Number", "Molarity (M)", "Pressure (atm)"])

    # Separates the chemical equation into its reactants and products.
    chemical_equation = raw_chemical_equation.replace(" ", "").split("<=>")
    # Formats and splits the reactants and products into individual formulas.
    reactants = list(map(subscript, chemical_equation[0].split("+")))
    products = list(map(subscript, chemical_equation[1].split("+")))
    # Rejoins the reactants and products into a stylized chemical equation.
    chemical_equation = " ⇌ ".join([" + ".join(reactants), " + ".join(products)])

    def get_values(formulas: list[str], formula_type: str, type: str) -> tuple[list[float], list[int]]:
        """Gets the molarity values of chemical formulas through inputs from the user.

        Args:
            formulas (list[str]): The chemical formulas.
            formula_type (str): The type of the thermodynamic values.
            type (str): The type of equilibrium constant

        Returns:
            tuple[list[float], list[int]]: The user given values.
        """
        # Create lists to store the values and coefficients of the given formulas.
        values: list[float] = []
        coefficients: list[int] = []

        for formula in formulas:
            # Resets the variable to allow for looping if inputted value is invalid
            successful = False

            # Loops the input prompt until the user gives a valid value.
            while not successful:
                # Tries to prompt the user to input the values.
                try:
                    if formula[0].isdigit():
                        # Separates the parts of the given chemical formula into its coefficient and main.
                        coefficient = int(formula[0])
                        main_formula = formula[1:]

                        # Asks the user for the value and exponentiates it to the coefficient.
                        given_value = float(
                            input(
                                f'\nPlease input the {"MOLARITY (M)" if type == "c" else "PRESSURE (atm)"} of "{main_formula}" (float or int ONLY): '
                            )
                        )
                        value = given_value**coefficient

                        # Adds the given values to the table of givens
                        givens_table.add_row(  # type: ignore
                            [
                                main_formula,
                                formula_type,
                                coefficient,
                                f"{given_value} M" if type == "c" else "N/A",
                                f"{given_value} atm" if type == "p" else "N/A",
                            ]
                        )

                        coefficients.append(coefficient)
                    else:
                        # Asks the user for the value.
                        value = given_value = float(
                            input(
                                f'\nPlease input the {"MOLARITY (M)" if type == "c" else "PRESSURE (atm)"} of "{formula}" (float or int ONLY): '
                            )
                        )

                        # Adds the given values to the table of givens
                        givens_table.add_row(  # type: ignore
                            [
                                formula,
                                formula_type,
                                1,
                                f"{given_value} M" if type == "c" else "N/A",
                                f"{given_value} atm" if type == "p" else "N/A",
                            ]
                        )

                        coefficients.append(1)

                    # Adds the given values to the list that will be returned by the function
                    values.append(value)

                    # Stops the input prompt from repeating.
                    successful = True
                # Catches error exception for when the given value is invalid.
                except ValueError:
                    # Informs the user what values are valid.
                    print("\nThe given value must be a valid float or int ONLY.")

                    # Repeats the input prompt.
                    successful = False

        # Returns the list of given values and formula coefficients.
        return values, coefficients

    def calculate_m(
        product_molarities: list[float],
        product_moles: list[int],
        reactant_molarities: list[float],
        reactant_moles: list[int],
    ) -> tuple[float, float]:
        """Calculates the equilibrium constant of the molarities of the reactants and products.

        Args:
            product_molarities (list[float]): The molarities of the products.
            product_moles (list[int]): The moles of the products.
            reactant_molarities (list[float]): The molarities of the reactants.
            reactant_moles (list[int]):The moles of the products.

        Returns:
            float: The calculated equilibrium constant.
        """
        # Opens the file where the results are contained.
        file = open(file_path, "a", encoding="utf-8")

        # Writes to the file the equation that will be used to calculate the equilibrium constant.
        file.write("\n\nEquation for the equilibrium constant (Kc):\nKc = [B]ᵇ / [A]ᵃ")

        # Writes to the file the solution for calculating the equilibrium constant.
        file.write(f'\n\nSolution for the equilibrium constant (Kc) of "{chemical_equation}":')
        file.write(
            f"\nKc = ({' × '.join(map(str, product_molarities))}) / ({' × '.join(map(str, reactant_molarities))})"
        )

        # Calculates the equilibrium constant.
        kc = reduce(lambda x, y: x * y, product_molarities) / reduce(lambda x, y: x * y, reactant_molarities)

        # Writes to the file the calculated equilibrium constant.
        file.write(f"\nKc = {kc}")

        file.write(f"\nKc = 1 / {kc}")

        # Calculates the backwards equilibrium constant.
        backward_kc = 1 / kc

        # Writes to the file the calculated backwards equilibrium constant.
        file.write(f"\nKc of backward = {backward_kc}")

        # Checks if the equilibrium constant is greater than zero then writes to the file that forward is favored.
        if kc > 0:
            file.write("\n\nBecause the equilibrium constant (Kc) is greater than 0, FORWARD is more favored.")
        # Checks if the equilibrium constant is less than zero then writes to the file that backward is favored.
        elif kc < 0:
            file.write("\n\nBecause the equilibrium constant (Kc) is less than 0, BACKWARD is more favored.")
        # Writes to the file that the reaction is at equilibrium.
        else:
            file.write(
                "\n\nBecause the equilibrium constant (Kc) is equal to 0, the reaction would not proceed and no products formed."
            )

        # Writes to the file the equation that will be used to calculate the equilibrium constant.
        file.write("\n\nEquation for the equilibrium constant (Kp):\nKp = Kc(0.0821 × T)ⁿ")

        # Writes to the file the solution for calculating the equilibrium constant.
        file.write(f'\n\nSolution for the equilibrium constant (Kp) of "{chemical_equation}":')
        file.write("\nT = 800 C + 273.15\nT = 1073.15 K")
        file.write(f"\nΔn = {fsum(product_moles)} - {fsum(reactant_moles)}")

        # Calculates the number of moles.
        moles = fsum(product_moles) - fsum(reactant_moles)

        file.write(f"\nΔn = {moles} mole/s")
        file.write(f"\nKp = {kc}(0.0821 × 1073.15 K){superscript(str(int(moles)))}")

        # Calculates the equilibrium constant.
        kp = 0.0821 * 1073.15
        kp **= moles
        kp *= kc

        # Writes to the file the calculated equilibrium constant.
        file.write(f"\nKp = {kp}")

        # Closes the opened file.
        file.close()

        # Returns the calculated equilibrium constant.
        return kc, kp

    def calculate_p(
        product_pressures: list[float],
        product_moles: list[int],
        reactant_pressures: list[float],
        reactant_moles: list[int],
    ) -> tuple[float, float]:
        """Calculates the equilibrium constant of the pressures of the reactants and products.

        Args:
            product_pressures (list[float]): The pressures of the products.
            product_moles (list[int]): The moles of the products.
            reactant_pressures (list[float]): The pressures of the reactants.
            reactant_moles (list[int]):The moles of the products.

        Returns:
            float: The calculated equilibrium constant.
        """
        # Opens the file where the results are contained.
        file = open(file_path, "a", encoding="utf-8")

        # Writes to the file the equation that will be used to calculate the equilibrium constant.
        file.write("\n\nEquation for the equilibrium constant (Kp):\nKp = [Pb]ᵇ / [Pa]ᵃ")

        # Writes to the file the solution for calculating the equilibrium constant.
        file.write(f'\n\nSolution for the equilibrium constant (Kp) of "{chemical_equation}":')
        file.write(f"\nKp = ({' × '.join(map(str, product_pressures))}) / ({' × '.join(map(str, reactant_pressures))})")

        # Calculates the equilibrium constant.
        kp = reduce(lambda x, y: x * y, product_pressures) / reduce(lambda x, y: x * y, reactant_pressures)

        # Writes to the file the calculated equilibrium constant.
        file.write(f"\nKp = {kp}")

        # Writes to the file the equation that will be used to calculate the equilibrium constant.
        file.write("\n\nEquation for the equilibrium constant (Kc):\nKc = Kp / (0.0821 × T)ⁿ")

        # Writes to the file the solution for calculating the equilibrium constant.
        file.write(f'\n\nSolution for the equilibrium constant (Kc) of "{chemical_equation}":')
        file.write("\nT = 800 C + 273.15\nT = 1073.15 K")
        file.write(f"\nΔn = {fsum(product_moles)} - {fsum(reactant_moles)}")

        # Calculates the number of moles.
        moles = fsum(product_moles) - fsum(reactant_moles)

        file.write(f"\nΔn = {moles} mole/s")
        file.write(f"\nKc = {kp} / (0.0821 × 1073.15 K){superscript(str(int(moles)))}")

        # Calculates the equilibrium constant.
        kc = 0.0821 * 1073.15
        kc **= moles
        kc = kp / kc

        # Writes to the file the calculated equilibrium constant.
        file.write(f"\nKc = {kc}")

        file.write(f"\nKc = 1 / {kc}")

        # Calculates the backwards equilibrium constant.
        backward_kc = 1 / kc

        # Writes to the file the calculated backwards equilibrium constant.
        file.write(f"\nKc of backward = {backward_kc}")

        # Checks if the equilibrium constant is greater than zero then writes to the file that forward is favored.
        if kc > 0:
            file.write("\n\nBecause the equilibrium constant (Kc) is greater than 0, FORWARD is more favored.")
        # Checks if the equilibrium constant is less than zero then writes to the file that backward is favored.
        elif kc < 0:
            file.write("\n\nBecause the equilibrium constant (Kc) is less than 0, BACKWARD is more favored.")
        # Writes to the file that the reaction is at equilibrium.
        else:
            file.write(
                "\n\nBecause the equilibrium constant (Kc) is equal to 0, the reaction would not proceed and no products formed."
            )

        # Closes the opened file.
        file.close()

        # Returns the calculated equilibrium constant.
        return kc, kp

    def is_valid(formula: str) -> bool:
        """Checks whether a formula is valid or not.

        Args:
            formula (str): The chemical formula.

        Returns:
            bool: Whether a formula is valid or not.
        """
        # Creates a list of chemical states to disregard.
        disregard = ["s)", "l)"]
        # Takes the formula's state.
        formula_state = formula.split("(")[1]

        # Checks if the formula should be disregarded.
        if formula_state in disregard:
            return False
        else:
            return True

    # Filters out the solid and liquid formulas.
    reactants = list(filter(is_valid, reactants))
    products = list(filter(is_valid, products))

    # Creates or opens a file to store where the results will be contained.
    file = open(file_path, "w+", encoding="utf-8")

    # Writes to the file the given chemical equation.
    file.write(f"The given chemical equation:\n{chemical_equation}")

    # Resets the variable to allow for looping if inputted value is invalid
    successful = False

    # Loops the input prompt until the user gives a valid "Y" or "n" value.
    while not successful:
        # Asks the user whether they would be using pressure or not.
        given_equilibrium_type = input("Please input if you would be using pressure (Y/n): ")

        # Checks whether the given input is a "Y" value.
        if given_equilibrium_type == "Y":
            # Replaces the "Y" fot yes with the "p" for pressure.
            equilibrium_type = "p"

            # Stops the input prompt from repeating.
            successful = True
        # Checks whether the given input is a "n" value.
        elif given_equilibrium_type == "n":
            # Replaces the "n" fot no with the "c" for moles.
            equilibrium_type = "c"

            # Stops the input prompt from repeating.
            successful = True
        else:
            # Informs the user what values are valid.
            print('\nThe given value must be either "Y" or "n" only.')

            # Repeats the input prompt.
            successful = False
            continue

    # Gets the values of the reactants and products.
    reactant_values, reactant_moles = get_values(
        reactants,
        "Reactants",
        equilibrium_type,  # type: ignore
    )
    product_values, product_moles = get_values(
        products,
        "Products",
        equilibrium_type,  # type: ignore
    )

    # Writes to the file the table of givens.
    file.write("\n\nGivens:")
    file.write("\n" + givens_table.get_string())  # type: ignore

    # Checks if the values are pressures.
    if equilibrium_type == "p":  # type: ignore
        # Writes to the file the required values to be calculated.
        file.write("\n\nRequired:\nKp and Kc")

        # Closes the created or opened file.
        file.close()

        # Calculates for the required values.
        kc, kp = calculate_p(
            product_values,
            product_moles,
            reactant_values,
            reactant_moles,
        )

        # Opens the file where the results are contained.
        file = open(file_path, "a+", encoding="utf-8")

        # Writes to the file the final answers to the required values.
        file.write("\n\nThe FINAL ANSWERS:")
        file.write(f"\nKp = {kp}")
        file.write(f"\nKc = {kc}")
    else:
        # Writes to the file the required values to be calculated.
        file.write("\n\nRequired:\nKc and Kp")

        # Closes the created or opened file.
        file.close()

        # Calculates for the required values.
        kc, kp = calculate_m(
            product_values,
            product_moles,
            reactant_values,
            reactant_moles,
        )

        # Opens the file where the results are contained.
        file = open(file_path, "a+", encoding="utf-8")

        # Writes to the file the final answers to the required values.
        file.write("\n\nThe FINAL ANSWERS:")
        file.write(f"\nKc = {kc}")
        file.write(f"\nKp = {kp}")

    # Closes the opened file.
    file.close()


def calculate_acids_and_bases() -> None:
    """Runs the acids and bases calculator."""

    def calculate_concentration(p: float, type: str) -> float:
        """Calculates the ion concentration of the potential.

        Args:
            p (float): The potential.
            type (str): The type of ion concentration.

        Returns:
            float: The calculated ion concentration.
        """
        # Opens the file where the results are contained.
        file = open(file_path, "a", encoding="utf-8")

        if type == "H":
            # Writes to the file the equation that will be used to calculate the hydrogen ion concentration.
            file.write("\n\nEquation for the hydrogen ion (H⁺):\n[H⁺] = 10⁻ᵖᴴ")

            # Writes to the file the solution for calculating the hydrogen ion concentration.
            file.write(f'\n\nSolution for the hydrogen ion (H⁺) of "pH = {p}":')
            file.write(f"\n[H⁺] = 10⁻{superscript(str(round(p)))}")

            # Calculates the hydrogen ion concentration.
            h = p * -1
            h = 10**h

            # Writes to the file the calculated hydrogen ion concentration.
            file.write(f"\n[H⁺] = {h} M")

            # Checks if the pH is greater than 7 then writes to the file that the solution is acidic.
            if h > 0.0000001:
                file.write("\n\nBecause the hydrogen ion (H⁺) is greater than 1 × 10⁻⁷, the solution must be ACIDIC.")
            # Checks if the pH is less than 7 then writes to the file that the solution is basic.
            elif h < 0.0000001:
                file.write("\n\nBecause the hydrogen ion (H⁺) is less than 1 × 10⁻⁷, the solution must be BASIC.")
            # Writes to the file that the solution is neutral.
            else:
                file.write("\n\nBecause the hydrogen ion (H⁺) is equal to 1 × 10⁻⁷, the solution must be NEUTRAL.")
        else:
            # Writes to the file the equation that will be used to calculate the hydroxide ion concentration.
            file.write("\n\nEquation for the hydroxide ion (OH⁻):\n[OH⁻] = 10⁻ᵖᴼᴴ")

            # Writes to the file the solution for calculating the hydroxide ion concentration.
            file.write(f'\n\nSolution for the hydroxide ion (OH⁻) of "pOH = {p}":')
            file.write(f"\n[OH⁻] = 10⁻{superscript(str(round(p)))}")

            # Calculates the hydroxide ion concentration.
            h = p * -1
            h = 10**h

            # Writes to the file the calculated hydroxide ion concentration.
            file.write(f"\n[OH⁻] = {h} M")

        # Closes the opened file.
        file.close()

        # Returns the calculated ion concentration.
        return h

    def calculate_potential(h: float, type: str) -> float:
        """Calculates the potential of the ion concentration.

        Args:
            h (float): The ion concentration.
            type (str): The type of potential.

        Returns:
            float: The calculated potential.
        """
        # Opens the file where the results are contained.
        file = open(file_path, "a", encoding="utf-8")

        if type == "H":
            # Writes to the file the equation that will be used to calculate the potential of hydrogen ion.
            file.write("\n\nEquation for the potential of hydrogen ion (H⁺):\npH = -log[H⁺]")

            # Writes to the file the solution for calculating the potential of hydrogen ion.
            file.write(f'\n\nSolution for the potential of hydrogen ion (H⁺) of "[H⁺] = {h}":')
            file.write(f"\npH = -log({h})")

            # Calculates the potential of hydrogen ion.
            p = log10(h) * -1

            # Writes to the file the calculated potential of hydrogen ion.
            file.write(f"\npH = {p}")

            # Checks if the pH is greater than 7 then writes to the file that the solution is basic.
            if p > 7:
                file.write(
                    "\n\nBecause the potential of hydrogen ion (pH) is greater than 7, the solution must be BASIC."
                )
            # Checks if the pH is less than 7 then writes to the file that the solution is acidic.
            elif p < 7:
                file.write(
                    "\n\nBecause the potential of hydrogen ion (pH) is less than 7, the solution must be ACIDIC."
                )
            # Writes to the file that the solution is neutral.
            else:
                file.write(
                    "\n\nBecause the potential of hydrogen ion (pH) is equal to 0, the solution must be NEUTRAL."
                )
        else:
            # Writes to the file the equation that will be used to calculate the potential of hydroxide ion.
            file.write("\n\nEquation for the potential of hydroxide ion (OH⁻):\npOH = -log[OH⁻]")

            # Writes to the file the solution for calculating the potential of hydroxide ion.
            file.write(f'\n\nSolution for the potential of hydroxide ion (OH⁻) of "[OH⁻] = {h}":')
            file.write(f"\npOH = -log({h})")

            # Calculates the potential of hydroxide ion.
            p = log10(h) * -1

            # Writes to the file the calculated potential of hydroxide ion.
            file.write(f"\npOH = {p}")

        # Closes the opened file.
        file.close()

        # Returns the calculated potential of ion concentration.
        return p

    def convert_potential(p: float, type: str) -> float:
        """Converts the potential of hydrogen ion to the potential of hydroxide ion and vice-versa.

        Args:
            p (float): The potential.
            type (str): The type of potential.

        Returns:
            float: The converted potential.
        """
        # Calculates the other potential and returns it.

        # Opens the file where the results are contained.
        file = open(file_path, "a", encoding="utf-8")

        # Checks if the type is "pOH".
        if type == "pOH":
            # Writes to the file the equation that will be used to convert the potential.
            file.write(f"\n\nEquation for converting the potential:\n{type} = 14 - pH")
        else:
            # Writes to the file the equation that will be used to convert the potential.
            file.write(f"\n\nEquation for converting the potential:\n{type} = 14 - pOH")

        # Writes to the file the solution for convert the potential.
        file.write("\n\nSolution for converting the potential:")
        file.write(f"\n{type} = 14 - {p}")

        # Calculates the potential conversion.
        p = 14 - p

        # Writes to the file the converted potential.
        file.write(f"\n{type} = {p}")

        # Closes the opened file.
        file.close()

        # Returns the converted potential.
        return p

    # Creates or opens a file to store where the results will be contained.
    file = open(file_path, "w+", encoding="utf-8")

    # Resets the variable to allow for looping if inputted value is invalid
    successful = False

    # Loops the input prompt until the user gives a valid value.
    while not successful:
        # Asks the user what value they have.
        given_required = input("\nPlease input what value you have (pH/H/pOH/OH): ")

        # Checks whether the given input is a "pH" value.
        if given_required == "pH":
            # Tries to prompt the user to input the molarity values.
            try:
                given_ph = float(input("\nPlease input the pH (float or int ONLY): "))

                if given_ph > 14:
                    # Informs the user what values are valid.
                    print("\nThe given pH value must be less than or equal to 14.")

                    # Repeats the input prompt.
                    successful = False
                elif given_ph < 0:
                    # Informs the user what values are valid.
                    print("\nThe given pH value must be greater than or equal to 0.")

                    # Repeats the input prompt.
                    successful = False

                # Writes to the file the given pH.
                file.write("Givens:")
                file.write(f"\npH = {given_ph}")

                # Writes to the file the required values to be calculated.
                file.write("\n\nRequired:\n[H⁺], pOH, and [OH⁻]")

                # Closes the created or opened file.
                file.close()

                h = calculate_concentration(given_ph, "H")
                poh = convert_potential(given_ph, "pOH")
                oh = calculate_concentration(poh, "OH")

                # Opens the file where the results are contained.
                file = open(file_path, "a+", encoding="utf-8")

                # Writes to the file the final answers to the required values.
                file.write("\n\nThe FINAL ANSWERS:")
                file.write(f"\n[H⁺] = {h}")
                file.write(f"\npOH = {poh}")
                file.write(f"\n[OH⁻] = {oh}")

                # Closes the opened file.
                file.close()

                # Stops the input prompt from repeating.
                successful = True
            # Catches error exception for when the given value is invalid.
            except ValueError:
                # Informs the user what values are valid.
                print("\nThe given pH value must be a valid float or int ONLY.")

                # Repeats the input prompt.
                successful = False
        # Checks whether the given input is a "H" value.
        elif given_required == "H":
            # Tries to prompt the user to input the molarity values.
            try:
                given_h = float(input("\nPlease input the H⁺ (float or int ONLY): "))

                # Writes to the file the given pH.
                file.write("Givens:")
                file.write(f"\n[H⁺] = {given_h}")

                # Writes to the file the required values to be calculated.
                file.write("\n\nRequired:\npH, pOH, and [OH⁻]")

                # Closes the created or opened file.
                file.close()

                ph = calculate_potential(given_h, "H")
                poh = convert_potential(ph, "pOH")
                oh = calculate_concentration(poh, "OH")

                # Opens the file where the results are contained.
                file = open(file_path, "a+", encoding="utf-8")

                # Writes to the file the final answers to the required values.
                file.write("\n\nThe FINAL ANSWERS:")
                file.write(f"\npH = {ph}")
                file.write(f"\npOH = {poh}")
                file.write(f"\n[OH⁻] = {oh}")

                # Closes the opened file.
                file.close()

                # Stops the input prompt from repeating.
                successful = True
            # Catches error exception for when the given value is invalid.
            except ValueError:
                # Informs the user what values are valid.
                print("\nThe given [H⁺] value must be a valid float or int ONLY.")

                # Repeats the input prompt.
                successful = False
        # Checks whether the given input is a "pOH" value.
        elif given_required == "pOH":
            # Tries to prompt the user to input the molarity values.
            try:
                given_poh = float(input("\nPlease input the pOH (float or int ONLY): "))

                if given_poh > 14:
                    # Informs the user what values are valid.
                    print("\nThe given pOH value must be less than or equal to 14.")

                    # Repeats the input prompt.
                    successful = False
                elif given_poh < 0:
                    # Informs the user what values are valid.
                    print("\nThe given pOH value must be greater than or equal to 0.")

                    # Repeats the input prompt.
                    successful = False

                # Writes to the file the given pH.
                file.write("Givens:")
                file.write(f"\npOH = {given_poh}")

                # Writes to the file the required values to be calculated.
                file.write("\n\nRequired:\n[OH⁻], pH, and [H⁺]")

                # Closes the created or opened file.
                file.close()

                oh = calculate_concentration(given_poh, "OH")
                ph = convert_potential(given_poh, "pH")
                h = calculate_concentration(ph, "H")

                # Opens the file where the results are contained.
                file = open(file_path, "a+", encoding="utf-8")

                # Writes to the file the final answers to the required values.
                file.write("\n\nThe FINAL ANSWERS:")
                file.write(f"\n[OH⁻] = {oh}")
                file.write(f"\npH = {ph}")
                file.write(f"\n[H⁺] = {h}")

                # Closes the opened file.
                file.close()

                # Stops the input prompt from repeating.
                successful = True
            # Catches error exception for when the given value is invalid.
            except ValueError:
                # Informs the user what values are valid.
                print("\nThe given pOH value must be a valid float or int ONLY.")

                # Repeats the input prompt.
                successful = False
        # Checks whether the given input is a ")H" value.
        elif given_required == "OH":
            # Tries to prompt the user to input the molarity values.
            try:
                given_oh = float(input("\nPlease input the OH⁻ (float or int ONLY): "))

                # Writes to the file the given pH.
                file.write("Givens:")
                file.write(f"\n[OH⁻] = {given_oh}")

                # Writes to the file the required values to be calculated.
                file.write("\n\nRequired:\npOH, pH, and [H⁺]")

                # Closes the created or opened file.
                file.close()

                poh = calculate_potential(given_oh, "OH")
                ph = convert_potential(poh, "pH")
                h = calculate_concentration(ph, "H")

                # Opens the file where the results are contained.
                file = open(file_path, "a+", encoding="utf-8")

                # Writes to the file the final answers to the required values.
                file.write("\n\nThe FINAL ANSWERS:")
                file.write(f"\npOH = {poh}")
                file.write(f"\npH = {ph}")
                file.write(f"\n[H⁺] = {h}")

                # Closes the opened file.
                file.close()

                # Stops the input prompt from repeating.
                successful = True
            # Catches error exception for when the given value is invalid.
            except ValueError:
                # Informs the user what values are valid.
                print("\nThe given [OH⁻] value must be a valid float or int ONLY.")

                # Repeats the input prompt.
                successful = False
        else:
            # Informs the user what values are valid.
            print('\nThe given value must be a "ph", "H", "pOH, or "OH" only.')

            # Repeats the input prompt.
            successful = False
            continue


# Defines whether to rerun the script or not.
rerun = True

# Keeps rerunning the script while rerun is true.
while rerun:
    # Resets the variable to allow for looping if inputted value is invalid
    successful = False

    # Loops the input prompt until the user gives a valid chemical equation and temperature value.
    while not successful:
        # Gives the user the instructions for providing the topic.
        print(
            dedent("""
            Please input the corresponding integer for the General Chemistry topic that you need this calculator for.
            1.) Thermochemistry
            2.) Chemical Kinetics
            3.) Chemical Equilibrium
            4.) Acids and Bases
            """)
        )
        # Asks the user for the topic.
        given_topic = input("Topic: ")

        # Checks whether the given input is a "1" value.
        if given_topic == "1":
            # Resets the variable to allow for looping if inputted value is invalid
            successful = False

            # Loops the input prompt until the user gives a valid chemical equation.
            while not successful:
                # Gives the user the instructions for providing the chemical equation to use.
                print("\nPlease input your chemical equation, this is case sensitive.\ne.g. N2 + 3H2 -> 2NH3")
                # Asks the user for the chemical equation to use.
                given_chemical_equation = input("\nChemical Equation: ")

                # Checks if the there was no chemical equation given.
                if given_chemical_equation == "":
                    # Informs the user that they need to provide a chemical equation.
                    print("\nYou NEED provide a chemical equation.")

                    # Repeats the input prompt.
                    successful = False

                # Tries to run the chemical equilibrium calculator
                try:
                    calculate_thermochemistry(given_chemical_equation)  # type: ignore

                    # Stops the input prompt from repeating.
                    successful = True

                except IndexError:
                    # Informs the user that their chemical equation does not follow the format.
                    print("\nThe chemical equation MUST follow the necessary format.")

                    # Repeats the input prompt.
                    successful = False

            # Stops the input prompt from repeating.
            successful = True
        # Checks whether the given input is a "2" value.
        elif given_topic == "2":
            # Runs the chemical kinetics calculator
            calculate_chemical_kinetics()  # type: ignore

            # Stops the input prompt from repeating.
            successful = True
        # Checks whether the given input is a "3" value.
        elif given_topic == "3":
            # Resets the variable to allow for looping if inputted value is invalid
            successful = False

            # Loops the input prompt until the user gives a valid chemical equation.
            while not successful:
                # Gives the user the instructions for providing the chemical equation to use.
                print("\nPlease input your chemical equation, this is case sensitive.\ne.g. N2O4(g) <=> 2NO2(g)")
                # Asks the user for the chemical equation to use.
                given_chemical_equation = input("\nChemical Equation: ")

                # Checks if the there was no chemical equation given.
                if given_chemical_equation == "":
                    # Informs the user that they need to provide a chemical equation.
                    print("\nYou NEED provide a chemical equation.")

                    # Repeats the input prompt.
                    successful = False

                # Tries to run the chemical equilibrium calculator
                try:
                    calculate_chemical_equilibrium(given_chemical_equation)  # type: ignore

                    # Stops the input prompt from repeating.
                    successful = True
                except IndexError:
                    # Informs the user that their chemical equation does not follow the format.
                    print("\nThe chemical equation MUST follow the necessary format.")

                    # Repeats the input prompt.
                    successful = False

            # Stops the input prompt from repeating.
            successful = True
        # Checks whether the given input is a "4" value.
        elif given_topic == "4":
            # Runs the chemical equilibrium calculator
            calculate_acids_and_bases()  # type: ignore

            # Stops the input prompt from repeating.
            successful = True
        else:
            # Informs the user what values are valid.
            print('\nThe given value must be "1", "2", "3", or "4" only.')

            # Repeats the input prompt.
            successful = False
            continue

    # Reopens the file where the results are contained for reading.
    file = open(file_path, "r", encoding="utf-8")

    # Reads the results contained in the file.
    file_contents = file.read()

    # Prints out the results.
    print("\n" + file_contents)

    # Closes the opened file.
    file.close()

    # Resets the variable to allow for looping if inputted value is invalid
    successful = False

    # Loops the input prompt until the user gives a valid "Y" or "n" value.
    while not successful:
        # Asks the user whether they want to keep the generated file or not.
        delete_file = input("Do you want to keep the generated file containing the results? (Y/n): ")

        # Checks whether the given input is a "n" value.
        if delete_file == "n":
            # Deletes the generated file where the results are contained.
            remove(file_path)

            # Prints out a confirmation of the file's deletion.
            print("\nThe file was successfully deleted.")

            # Stops the input prompt from repeating.
            successful = True
        # Checks whether the given input is a "Y" value.
        elif delete_file == "Y":
            # Prints out the location of where the file was generated.
            print(f"\nThe file was generated at: {path.realpath(file_path)}\n")

            # Stops the input prompt from repeating.
            successful = True
        else:
            # Informs the user what values are valid.
            print('\nThe given value must be either "Y" or "n" only.')

            # Repeats the input prompt.
            successful = False

    # Resets the variable to allow for looping if inputted value is invalid
    successful = False

    # Loops the input prompt until the user gives a valid "Y" or "n" value.
    while not successful:
        # Asks the user whether they want to rerun the script or not.
        delete_file = input("Do you want to rerun the script? (Y/n): ")

        # Checks whether the given input is a "n" value.
        if delete_file == "n":
            # Stops the script from rerunning.
            rerun = False

            # Stops the input prompt from repeating.
            successful = True
        # Checks whether the given input is a "Y" value.
        elif delete_file == "Y":
            # Stops the input prompt from repeating.
            successful = True
        else:
            # Informs the user what values are valid.
            print('\nThe given value must be either "Y" or "n" only.')

            # Repeats the input prompt.
            successful = False
