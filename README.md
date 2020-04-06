# Watering Machine
Modular Watering Machine (Arduino compatible)



Generate UML class diagram of States
hpp2plantuml -i "./src/WateringMachine/States/*.h" -o docs/uml/states.puml

Generate UML class diagram of Components
hpp2plantuml -i "./src/WateringMachine/Components/*.h" -i "./src/WateringMachine/Components/StateMachineInterfaces/*.h" -o docs/uml/components.puml

Generate UML class diagram of All Components and States
hpp2plantuml -i "./src/WateringMachine/*.h" -i "./src/WateringMachine/States/*.h" -i "./src/WateringMachine/Components/*.h" -i "./src/WateringMachine/Components/StateMachineInterfaces/*.h" -o docs/uml/all.puml

## LICENSE
Apache License
Version 2.0, January 2004
                        http://www.apache.org/licenses/