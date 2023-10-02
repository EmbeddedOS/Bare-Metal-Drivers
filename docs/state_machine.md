# Finite state machine

- What is a state machine (FSM)?
  - A state machine is a software model of computation, and it comprises finite number states.
  - Since states are finite, there is a finite number of transitions among the states. Transitions are triggered by the input events fed to the state machine (FSM is an event-driven system).
  - A state machine also produces an output. The output produced depends on the current state of the state machine and the input events fed to the state machine.

- Benefits of using state machines (FSMs):
  - 1. Used to describe situations or scenarios of your application (Modelling the life cycle of a reactive object through interconnections of state).
  - 2. FSMs are helpful to model complex applications that involve lots of decision-making, producing different outputs (actions), and processing various events.
  - 3. State machines are visualize through state machine diagrams in the form of state charts, which helps to communicate between non-developers and developers.
  - 4. Makes it easier to visualize and implement the changes to the behavior of the project.
  - 5. Complex application can be visualize as a collection of different states processing a fixed set of events and producing a fixed set of outputs.
  - 6. Loose coupling: An application can be divided into multiple behaviors or state machines, and each unit can be tested separately or could be reused in other applications.
  - 7. Easy debugging and easy code maintenance.
  - 8. Scalable.
  - 9. Narrow down whole application complexity to state level complexity, analyze and implement.

- Different types of state machines:
  - Mealy machines.
  - Moore machines.
  - Harel state charts.
  - UML state machines.

- UML Modelling tool and code generator:
  - Rhapsody by IBM.
  - QM Model-based design tool by Quantum Leaps.
  - Visual State by IAR.
  - Yakinda state chart tools by Itemis AG.

## Mealy and Moore machine

- Mealy machine:
  - In this machine, the output produced by the state machine depends on the input events fed to the state machine AND present active state of the state machine.
  - The output is not produced inside the state UML modelling tool and code generator.

- Generic Mealy model:
  
```text
         ______     _______INPUT/OUTPUT_______     _____
        |     _||_||_                         || ||     |
        |    | State |                       _\/_\/_    |
INPUT/OUTPUT |_______|                      | State |  INPUT/OUTPUT
        |      /\ /\                        |_______|   |
        |______|| ||_______INPUT/OUTPUT_______|| ||_____|
```

- Output is represented along with each input separated by `/`.
- An `Output` is also called `Action`.
- In the mealy model, the `output` is also called `input action`.

- State 1 -> State 2: `INPUT/OUTPUT` also called as a `TRANSACTION`.

- For example:

    ```text

    Initial state
    Light Off
        ||
     ___\/______                               _____
    |  OFF      |-------ON/Dim the light----->| DIM |
    |___________|<------OFF/Light off---------|_____|<--------------|
        /\  /\                                  ||                  |
        ||  ||                              ON/Medium brightness    |
        ||  ||                                  ||                  |
        ||  ||                               ___\/__________        |
        ||  ||----------OFF/Light off-------| Medium bright |       |
        ||                                  |_______________|       |
        ||                                      ||                  |
        ||                                  ON/Full brightness      |
        ||                                      ||                  |
        ||                                   ___\/___               |
        ||--------------OFF/Light off-------| Bright |              |
                                            |________|              |
                                                ||__________________|
                                                ON/Dim the light
    ```

  - When state is off and INPUT = ON -> action is: Dim the light.
  - When state is DIM and INPUT = OFF -> action is: Light off.
  - When state is DIM and INPUT = ON -> action is: Medium brightness.
  - And so on.

- Moore machine
  - In this state machine, the output is determined only by the present active state of the state machine and not by any input events.
  - No output during state transition.
  - Output is represented inside the state.
  - `Output` is also called `Action`.
  - In the Moore model the `Output` is also called `Entry action.`.

```text
     ______     ___________INPUT__________     _____
    |     _||_||_                         || ||     |
    |    | State |                       _\/_\/_    |
  INPUT  |Output_|                      | State |  INPUT
    |      /\ /\                        |Output_|   |
    |______|| ||___________INPUT__________|| ||_____|
```

- For example:

    ```text

    Initial state
    Light Off
        ||
     ___\/______                               _____________
    |  OFF      |-------ON------------------->| DIM         |
    |_Light Off_|<------OFF-------------------|Dim the light|<------|
        /\  /\                                  ||                  |
        ||  ||                                  ON                  |
        ||  ||                                  ||                  |
        ||  ||                               ___\/____________      |
        ||  ||----------OFF-----------------| Medium bright   |     |
        ||                                  |Medium brightness|     |
        ||                                      ||                  |
        ||                                      ON                  |
        ||                                      ||                  |
        ||                                   ___\/__________        |
        ||--------------OFF-----------------| Bright        |       |
                                            |Full brightness|       |
                                                ||__________________|
                                                          ON
    ```

- Input events:
  - ON
  - OFF

- Entry actions:
  - 1. Light off.
  - 2. Dim the light.
  - 3. Make light dim.
  - 4. Make light medium brightness.
  - 5. Make light full brightness.

## Mealy and Moore State Transition Table

- State transition table Light control Mealy machine:

```text
|Present|                       Next state                          |
|state  |-----------------------------------------------------------|
|       |                       Input events                        |
|       |-----------------------------------------------------------|
|       |           OFF              |              ON              |
|       |----------------------------|------------------------------|
|       |Next state  |input action   |Next state |input action      |
|       |            |(output)       |           |(output)          |
|-------|------------|---------------|-----------|------------------|
|Off    |Off         |--ignored--    |Dim        | Make Light Dim   |
|-------|------------|---------------|-----------|------------------|
|Dim    |Off         |Light off      |Medium     | Make light medium|
|-------|------------|---------------|-----------|------------------|
|Medium |Off         |Light off      |Bright     | Make light bright|
|-------|------------|---------------|-----------|------------------|
|Bright |Off         |Light off      |Dim        | Make light dim   |
|-------|------------|---------------|-----------|------------------|
```

- State transition table Light Control Moore machine:

```text
|State  |Entry actions (output) |           Next state          |
|       |                       |-------------------------------|
|       |                       |           Input events        |
|       |                       |-------------------------------|
|       |                       |     OFF      |    ON          |
|       |                       |--------------|----------------|
|-------|-----------------------|--------------|----------------|
|Off    |Light off              |--ignored--   | DIM            |
|Dim    |Make light dim         |Off           | Medium         |
|Medium |Make light medium      |Off           | Bright         |
|Bright |Make light bright      |Off           | Dim            |
```

## Mealy coding exercise

- We handle event from user by using: `Serial.available()` method.
  
```C++

uint8_t current_state = OFF;

void light_state_machine(uint8_t state) {
    switch (current_state) {
        case OFF:
        {
            switch (state) {
                case ON:
                    make_dim_light();
                    current_state = DIM;
                    break;
                case OFF:
                    /* Ignore. */
                break;
            }
        }
        break;
        case DIM:
        {
            
        }
        break;
        case MEDIUM:
        {
            
        }
        break;
        case BRIGHT:
        {
            
        }
        break;
        default:
    }
}

void loop()
{
    uint8_t event;
    if (Serial.available() > 0) {
        event = Serial.read();
        if (event == 'o') {
            light_state_machine(ON);
        } else if (event == 'x') {
            light_state_machine(OFF);
        }
    }
}
```

## UML Flat state machine and implementation

### State machine definition

- What is a state?
  - State represents a distinct stage of an object's lifecycle.
  - A state models a situation in the execution of a StateMachine Behavior during some invariant condition holds. In most cases, this condition is not explicitly defined but is implied, usually through the name associated with the State.

- How do you arrive at fixing a state?
  - Map different scenarios through which an object lifecycle passes into number of states.

- Application -----Set behaviors----> Object
              \----Set attributes------>/

- How to create a state?
  - 1. Draw a round-concerned rectangle.
  - 2. Create a horizontal name compartment.
  - 3. Give a name that is unique within the state machine diagram.

- Types of states in UML:
  - 1. Simple State: If a state doesn't have any sub-states, transitions, regions, sub-machines then it's a simple state.
  - 2. Composite State.
  - 3. Submachine State.

- Composite state:
  - What is a composite state?
    - A state which has sub-states. A composite State contains at least one region.
      - 1. Simple composite state.
      - 2. Orthogonal state.
    - A simple composite state has exactly one region.
  - By using composite states, you can express state hierarchies.
  - It makes state-charts more comprehensible by reducing the number of transitions between sates.

- For example simple state, no regions, no sub states:

```text
 ___________________
|________S0_________|
|                   |
|___________________|
```

- Any state enclosed within a region of a composite state is called a sub-state of that composite state:

```text
 _________________________________________
|_____________________S1__________________|
|    _____________       _____________    |    
|   |____S1_0_____|     |____S1_1_____|   |
|   |             |     |             |   |
|   |_____________|     |_____________|   |
|    _____________                        |
|   |____S1_2_____|     Sequential        |
|   |             |     sub-states        |
|   |_____________|                       |
|_R1______________________________________|
```

- S1 is a composite state.
- S1 has 1 region R1.
- S1_x are sub-states of S1.
- S1 is a superstate of S1_x.
- S1_x is very simple states.

- For example, in-direct sub-states:

```text
 _______________________________________________________
|_____________________________S1________________________|
|                                                       |
|                                                       |
|    _____________                                      |
|   |____S1_1_____|                                     |
|   |             |                                     |
|   |_____________|                                     |
|        _________________________________________      |
|       |___________________S1_0__________________|     |
|       |    _____________       _____________    |     |
|       |   |___S1_0_1____|     |___S1_0_0____|   |     |
|       |   |             |     |             |   |     |
|       |   |_____________|     |_____________|   |     |
|       |    _____________                        |     |
|       |   |___S1_0_2____|                       |     |
|       |   |             |                       |     |
|       |   |_____________|                       |     |
|       |_R1______________________________________|     |
|_R1____________________________________________________|
```

- S1_0_1 is in-direct sub-state of S1.
- S1_0 is direct sub-state of S1.

### Demo based on example: Productivity Timer (ProTimer)

- The application that tracks your productive time.

### Astah UML download

- Download link: [link](https://astah.net/)

### Project Requirements

- 1. `+` button -> Increase time (minutes should increase)
- 2. `-` button -> Decrease time (minutes should decrease)
- 3. `S/P` button -> Start/pause the count down; show STAT.
- 4. When the countdown is paused, time can be modified.
- 5. Press the `+` and `-` button simultaneously to abort the running timer.
- 6. Application must beep 20 times when it returns to IDLE mode.
- 7. When the application is in IDLE mode, pressing the `S/P` button should show the STAT for 1 second and auto return to IDLE mode.

- Different scenarios of ProTimer application:
  - IDLE
  - TIME-SET
  - COUNTDOWN
  - PAUSE
  - STAT

- These are the different scenarios which the ProTimer application object lifecycle passes through.

### UML State machine internal state activities (entry/exit/do)

- Internal activities compartment
  - This compartment holds a list of internal behaviors associated with a state.
  - Each entry has following format:
    - `<behavior-type-label>['/'<behavior-expression>]`
  - Example:
    - `entry`, `exit`, `do` are internal activities labels or keywords defined in the UML. Do not use these keywords to represent events in the state machine diagram.

- Internal activity labels
  - These labels identify the circumstances under which the behaviors specified by the `behavior-expression` is executed.
  - 1. *entry*: Behavior identified by `<behavior-expression>` will be executed upon entry to the state. Use the *entry* keyword if the state has entry action.
  - 2. *exit*: Behavior identified by `<behavior-expression>` will be executed upon exit to the state. Use the *exit* keyword if a state has exit action.
  - 3. *do*: Behavior identified by `<behavior-expression>` will be executed as long as the object is in the state or until the computation specified by the expression is completed. This represents ongoing behavior. Use the *do* keyword only if a state has `do` action.
