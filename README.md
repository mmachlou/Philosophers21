# Dining Philosophers Problem

This project implements a solution to the **Dining Philosophers Problem** using threads and mutexes in C. The simulation adheres to the rules of the problem while focusing on thread synchronization, resource management, and timing accuracy.

## Description

The Dining Philosophers Problem is a classic concurrency problem where a group of philosophers alternates between eating, thinking, and sleeping. Each philosopher requires two forks to eat, which introduces potential deadlocks and starvation issues. This project simulates the problem while avoiding these pitfalls.

## Features

- Handles variable numbers of philosophers.
- Implements timing logic for each philosopher's actions (thinking, eating, sleeping).
- Avoids deadlocks and ensures that philosophers do not starve.
- Supports arguments to configure the simulation.

## Usage

### Compilation

Run the following command to compile the project:

```bash
make
```

This will generate an executable called `philo`.

### Execution

To run the program, use the following command:

```bash
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> <number_of_times_each_philosopher_must_eat>
```

#### Arguments

- `number_of_philosophers`: Number of philosophers (and forks) in the simulation.
- `time_to_die`: Time (in milliseconds) a philosopher can survive without eating.
- `time_to_eat`: Time (in milliseconds) a philosopher takes to eat.
- `time_to_sleep`: Time (in milliseconds) a philosopher takes to sleep.
- `number_of_times_each_philosopher_must_eat`: (Optional) Number of times each philosopher needs to eat before the simulation stops. If not specified or set to 0, the simulation runs indefinitely.

#### Example

```bash
./philo 5 800 200 200 3
```

In this example:
- There are 5 philosophers.
- A philosopher dies if they don't eat within 800ms.
- Eating takes 200ms, and sleeping takes 200ms.
- Each philosopher must eat at least 3 times before the simulation ends.

### Error Handling

The program checks for invalid input and will return an error message if:
- Any argument is missing or not a positive integer.
- `number_of_philosophers` is less than 1.

## Code Structure

- `philo.c`: Contains the `main` function and argument parsing.
- `routin.c`: Implements the philosopher's actions (thinking, eating, sleeping) and the main routine.
- `utils.c`: Includes utility functions such as precise sleeping and time calculations.
- `philo.h`: Header file with shared structures, macros, and function prototypes.
- `Makefile`: Build file to compile and clean the project.

## Output

The program outputs the philosophers' actions with timestamps:

```
<timestamp> Philosopher <id> is thinking
<timestamp> Philosopher <id> is eating
<timestamp> Philosopher <id> is sleeping
<timestamp> Philosopher <id> has died
```

## Known Issues

- Precision of timestamps may vary slightly depending on system load and hardware.
- In large simulations, scheduling delays might occur due to the OS thread scheduler.
