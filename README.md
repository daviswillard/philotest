# Philosophers

### About project:

• One or more philosophers sit at a round table.
There is a large bowl of spaghetti in the middle of the table.<br /><br />
• The philosophers alternatively eat, think, or sleep.
While they are eating, they are not thinking nor sleeping;
while thinking, they are not eating nor sleeping;
and, of course, while sleeping, they are not eating nor thinking.<br /><br />
• There are also forks on the table. There are as many forks as philosophers.<br /><br />
• Because serving and eating spaghetti with only one fork is very inconvenient, a
philosopher takes their right and their left forks to eat, one in each hand.<br /><br />
• When a philosopher has finished eating, they put their forks back on the table and
start sleeping. Once awake, they start thinking again. The simulation stops when
a philosopher dies of starvation.<br /><br />
• Every philosopher needs to eat and should never starve.<br /><br />
• Philosophers don’t speak with each other.<br /><br />
• Philosophers don’t know if another philosopher is about to die.<br /><br />

## The specific rules for this part are:<br />
• Each philosopher should be a thread.<br /><br />
• There is one fork between each pair of philosophers. Therefore, if there are several
philosophers, each philosopher has a fork on their left side and a fork on their right
side. If there is only one philosopher, there should be only one fork on the table.<br /><br />
• To prevent philosophers from duplicating forks, you should protect the forks state
with a mutex for each of them.<br /><br />

### How to start:
Program should take the following arguments:<br /><br />
number_of_philosophers   time_to_die   time_to_eat   time_to_sleep  [number_of_times_each_philosopher_must_eat]<br /><br />
◦ number_of_philosophers: The number of philosophers and also the number
![Screenshot_20221208_165839](https://user-images.githubusercontent.com/82828987/206464790-e0261b5e-4c2c-415d-b097-f9d1d39be018.png)
