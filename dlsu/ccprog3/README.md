# JavaJeeps

[![Maven Version](https://img.shields.io/badge/Maven-Latest-c71a36?logo=apachemaven&logoColor=c71a36)](https://maven.apache.org/)
[![JDK Version](https://img.shields.io/badge/OpenJDK-21-000000?logo=openjdk&logoColor=000000)](https://openjdk.org/)

A program that simulates managing and interacting with a coffee truck business. This program allows the user to manage
multiple coffee trucks and interact with them as a customer. Two applications are available: a CLI and a GUI-based
application. The two applications have the same features. The only difference will be because of the difference in UIs.

## Features

- **Truck Creation** - Multiple trucks can be created, and they can be regular or special trucks. Special trucks can
  carry syrup add-ons, set espresso ratios, and add extra espresso shots to coffees.
- **Truck Maintenance** - Trucks can have their storage bins emptied, filled, or their ingredients swapped. The trucks
  can also be moved, and their coffee prices adjusted (universally).
- **Coffee Sale** - Cups of coffee can be purchased from a specific truck. The coffee can be customized, with options
  depending on the truck type.
- **Dashboard** - Information about all transactions made, and the overall amounts of ingredients, can be viewed on a
  single screen.

## Compilation

```shell
mvn compile
```

## Usage

### CLI

```shell
mvn exec:java -Dexec.mainClass="cielsachen.javajeeps.mco1.Main"
```

### GUI

```shell
mvn exec:java
```

## Documentation

Generate the JavaDoc API documentation pages:

```shell
mvn javadoc:javadoc
```

---

<img
  alt="DLSU Seal"
  height="125px"
  src="https://upload.wikimedia.org/wikipedia/en/thumb/c/c2/De_La_Salle_University_Seal.svg/2048px-De_La_Salle_University_Seal.svg.png"
/>
<img
  alt="CCS Logo"
  height="125px"
  src="https://www.dlsu.edu.ph/wp-content/uploads/2019/06/ccs-logo.png"
/>

## De La Salle University (DLSU)

- Object-Oriented Programming (CCPROG3)
- Academic Year 2024-2025
- Year 1 (Undergraduate), Term 3
- Major Course Output 1 & 2 (MCO1 & 2)
