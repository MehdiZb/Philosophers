# Philosophers
Multithreading and mutex.

A group of philosophers sit around a round table with a large plate of spaghetti in the center and each has a fork.

They can either be eating, thinking, or sleeping.

When eating, they can't think or sleep. When sleeping, they can't eat or think.

When thinking, they can't eat or sleep.

A philosopher takes two forks, one from the left and one from the right, to eat.

Once finished eating, they put the forks down and sleep.

The simulation ends if a philosopher dies of hunger.

The number of philosophers, forks and durations of eating, thinking and sleeping are defined by the user.

This problem serves as a great learning tool for understanding the concept of multithreading in software development. By simulating the actions of philosophers, it showcases the need for synchronization and coordination among multiple threads to prevent deadlocks and starvation. The adjustable durations of eating, and sleeping, as well as the number of philosophers and forks, allow for a flexible and dynamic learning environment.

# Philosophers in action

./philo (3 Philos) (100ms to die) (30ms to eat) (20ms to sleep) (the simulation will keep going until every philosophers ate 3 times)

![image](https://user-images.githubusercontent.com/44801448/216532724-6d7c8339-c0f6-4f54-af3a-6b5292062d84.png)

./philo 3 100 50 50 5 (Dead philo)

![image](https://user-images.githubusercontent.com/44801448/216532785-56220452-8337-4830-9e1c-d909665cbe58.png)
 
 Visualization (https://nafuka11.github.io/philosophers-visualizer/)

![image](https://user-images.githubusercontent.com/44801448/216533459-9545e2e6-d85a-4a5c-b000-1ed5eb100cd1.png)

# Project Grade

![image](https://user-images.githubusercontent.com/44801448/216533572-9bbd520c-f4b6-4e40-adaf-bea94a97c73e.png)
