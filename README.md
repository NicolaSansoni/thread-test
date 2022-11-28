# Kernel level threads VS User level threads

## Requirements

- Linux (o WSL su Windows)
- libpth-dev
- pthread (su ubuntu è installato di default)

## Spiegazione

Gli user level threads sono forniti da GNU Pth.  
Per ogni thread richiesto viene creato uno user thread gestito dalla libreria
stessa. Tutti i threads condividono lo stesso kernel thread (e lo stesso
processo), quindi devono condividere le risorse fornite al processo dal kernel.
Condividono quindi lo spazio di indirizzi e memoria, ma condividono anche il singolo
thread "reale". Sono perfetti per applicazioni IO-bound, in quanto creare uno
user thread è molto leggero. Sono pessimi per applicazioni CPU-bound, in quanto
non possono avere accesso a più CPU core diversi.

I kernel level threads sono forniti da pthread.  
Per ogni thread richiesto viene creato un kernel thread che viene associato allo
user thread richiesto, così da condividere lo spazio di indirizzi del processo
ma utilizzando risorse di CPU separate, o qualcosa giù di lì.
In pratica ti prendi la condivisione di indirizzi e dati degli user level threads,
l´accesso ai core del multiprocessing, tutto per un piccolo costo di inizializzazione.
Visto che crearli è pesante spesso è conveniente pre-allocare una ThreadPool anziché
creare un nuovo thread ogni volta che arriva un nuovo task.

Multiprocessing è multiprocessing ed è fuori dallo scope di questo esempio.

## Esegui

- installa pthreads (se non è già installato), installa libpth-dev.
- lancia `make` per buildare gli esempi.

`bin/ult` lancia l'esempio per gli user level threads  
`bin/klt` lancia l'esempio per i kernel level threads

Entrambi eseguono lo stesso task, che è CPU bound.
Per vedere in prima persona le differenze puoi monitorare le risorse utilizzate
con `htop`.

Se sei su Windows usa WSL per creare un ambiente Linux su Windows.
