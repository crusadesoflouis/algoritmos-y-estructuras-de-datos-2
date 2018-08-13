#ifndef PLANIFICADOR_RR_H_
#define PLANIFICADOR_RR_H_

#include <iostream>
#include <cassert>

using namespace std;

/**
 * Se puede asumir que el tipo T tiene constructor por copia y operator==
 * No se puede asumir que el tipo T tenga operator=
 */
template<typename T>
class PlanificadorRR {

  public:

	/**
	 * Crea un nuevo planificador de tipo Round Robin.
	 */
//done
	PlanificadorRR();

	/**
	 * Una vez copiado, ambos planificadores deben ser independientes,
	 * es decir, por ejemplo, que cuando se borra un proceso en uno
	 * no debe borrarse en el otro.
	 */
//done
	PlanificadorRR(const PlanificadorRR<T>&);

	/**
	 * Acordarse de liberar toda la memoria!
	 */

//done
	~PlanificadorRR();



	/**
	 * Agrega un proceso al planificador. El mismo debe ubicarse,
	 * dentro del orden de ejecución, inmediatamente antes del que está
	 * siendo ejecutado actualmente. Si no hubiese ningún proceso en ejecución,
	 * la posición es arbitraria y el proceso pasa a ser ejecutado automáticamente.
	 * PRE: El proceso no está siendo planificado por el planificador.
	 */

//done
	void agregarProceso(const T&);

	/**
	 * Elimina un proceso del planificador. Si el proceso eliminado
	 * está actualmente en ejecución, automáticamente pasa a ejecutarse
	 * el siguiente (si es que existe).
	 * PRE: El proceso está siendo planificado por el planificador.
	 */
	void eliminarProceso(const T&);

	/**
	 * Devuelve el proceso que está actualmente en ejecución.
	 * PRE: Hay al menos un proceso activo en el planificador.
	 */

//done
	const T& procesoEjecutado() const;

	/**
	 * Procede a ejecutar el siguiente proceso activo,
	 * respetando el orden de planificación.
	 * PRE: Hay al menos un proceso activo en el planificador.
	 */
//done
	void ejecutarSiguienteProceso();

	/**
	 * Pausa un proceso por tiempo indefinido. Este proceso pasa
	 * a estar inactivo y no debe ser ejecutado por el planificador.
	 * Si el proceso pausado está actualmente en ejecución, automáticamente
	 * pasa a ejecutarse el siguiente (si es que existe).
	 * PRE: El proceso está siendo planificado por el planificador.
	 * PRE: El proceso está activo.
	 */
//done
	void pausarProceso(const T&);

	/**
	 * Reanuda un proceso previamente pausado. Este proceso pasa a estar
	 * nuevamente activo dentro del planificador. Si no había ningún proceso
	 * en ejecución, el proceso pasa a ser ejecutado automáticamente.
	 * PRE: El proceso está siendo planificado por el planificador.
	 * PRE: El proceso está inactivo.
	 */
//done
	void reanudarProceso(const T&);

	/**
	 * Detiene la ejecución de todos los procesos en el planificador
	 * para atender una interrupción del sistema.
	 * PRE: El planificador no está detenido.
	 */
//done
	void detener();

	/**
	 * Reanuda la ejecución de los procesos (activos) en el planificador
	 * luego de atender una interrupción del sistema.
	 * PRE: El planificador está detenido.
	 */
//done
	void reanudar();

	/**
	 * Informa si el planificador está detenido por el sistema operativo.
	 */

//done
	bool detenido() const;

	/**
	 * Informa si un cierto proceso está siendo planificado por el planificador.
	 */
//done
	bool esPlanificado(const T&) const;

	/**
	 * Informa si un cierto proceso eesPlanifstá activo en el planificador.
	 * PRE: El proceso está siendo planificado por el planificador.
	 */
//done
	bool estaActivo(const T&) const;

	/**
	 * Informa si existen procesos planificados.
	 */
//done
	bool hayProcesos() const;

	/**
	 * Informa si existen procesos activos.
	 */
//done
	bool hayProcesosActivos() const;

	/**
	 * Devuelve la cantidad de procesos planificados.
	 */
//done
	int cantidadDeProcesos() const;

	/**
	 * Devuelve la cantidad de procesos planificados y activos.
	 */
//done
	int cantidadDeProcesosActivos() const;

	/**
	 * Devuelve true si ambos planificadores son iguales.
	 */
//done
	bool operator==(const PlanificadorRR<T>&) const;

	/**
	 * Debe mostrar los procesos planificados por el ostream (y retornar el mismo).
	 * Los procesos deben aparecer en el mismo orden en el que son ejecutados
	 * por el planificador. Como la lista es circular, se decidió que el primer
	 * proceso que se muestra debe ser el que está siendo ejecutado en ese momento.
	 * En el caso particular donde exista al menos un proceso planificado,
	 * pero estén todos pausados, se puede comenzar por cualquier proceso.
	 * Un proceso inactivo debe ser identificado con el sufijo ' (i)'
	 * y el proceso que está siendo ejecutado, de existir, debe ser identificado
	 * con el sufijo '*'.
	 * PlanificadorRR vacio: []
	 * PlanificadorRR con 1 elemento activo: [p0*]
	 * PlanificadorRR con 2 elementos inactivos: [p0 (i), p1 (i)]
	 * PlanificadorRR con 3 elementos (p0 inactivo, p2 siendo ejecutado: [p2*, p0 (i), p1]
	 *
	 * OJO: con pX (p0, p1, p2) nos referimos a lo que devuelve el operador <<
	 * para cada proceso, es decir, cómo cada proceso decide mostrarse en el sistema.
	 * El sufijo 'X' indica el orden relativo de cada proceso en el planificador.
	 */

//enproceso
	ostream& mostrarPlanificadorRR(ostream&) const;

  private:

	/**
	 * No se puede modificar esta funcion.
	 */
	PlanificadorRR<T>& operator=(const PlanificadorRR<T>& otra) {
		assert(false);
		return *this;
	}

//esVacia
	bool esVacia ( const PlanificadorRR<T>& planificador){
	return (planificador.procesos == 0);
}

//struct del nodo
	struct Nodo {
	T elem;
	Nodo* siguiente;
	Nodo* anterior;
	bool activo;

	Nodo(const T& proceso,Nodo* sig, Nodo* ant,bool activ) : elem(proceso){
	siguiente = sig;
	anterior  = ant;
	activo = activ;
	}

	Nodo( const T& proceso) : elem(proceso){
	this->activo = true;
	siguiente = anterior = this;
	}
   };
	Nodo* enejecucion;
	bool interrupcion;
	int procesos;
	int activos;

};
//se cierra la clase

//constructor de inicializacion
	template <typename T>
	PlanificadorRR<T>::PlanificadorRR(){
	enejecucion = NULL;
	procesos = 0;
	activos = 0;
	interrupcion = false;
	}
//constructor por copia
	template <typename T>
	PlanificadorRR<T>::PlanificadorRR(const PlanificadorRR<T>& other){
	enejecucion = NULL;
	procesos = 0;
	activos = 0;
	interrupcion = false;
		Nodo* senialadorother = other.enejecucion;
	for (int i = 0; i< other.cantidadDeProcesos(); i++){
		this->agregarProceso(senialadorother->elem);
		senialadorother = senialadorother->siguiente;
		}
		Nodo* puntero= other.enejecucion;
		Nodo*punteroT= this->enejecucion;
	for (int i = 0; i< other.cantidadDeProcesos(); i++){
		if (puntero->activo== false){
			punteroT->activo = false;
      this->activos--;
		}
		puntero = puntero->siguiente;
		punteroT = punteroT->siguiente;
	}


}
	template <typename T>
	PlanificadorRR<T>::~PlanificadorRR(){
		while (this->procesos > 0){
			this->eliminarProceso(this->enejecucion->elem);
		}
	}


	template <typename T >
	void PlanificadorRR<T>::agregarProceso(const T& proceso){
		if (procesos == 0){

			Nodo* puntero = new Nodo(proceso);
			enejecucion = puntero;

		}

		else{
			if (activos == 0){
				Nodo* puntero  = new Nodo(proceso,enejecucion,enejecucion->anterior,true);
				enejecucion->anterior->siguiente = puntero;
				enejecucion->anterior = puntero;
				enejecucion = puntero;
				}
			else{
				Nodo*puntero = new Nodo(proceso,enejecucion,enejecucion->anterior,true);
				enejecucion->anterior->siguiente = puntero;
				enejecucion->anterior = puntero;
			}
		}

		this->procesos++;
		this->activos++;
	}

	template<typename T>
	void PlanificadorRR<T>::eliminarProceso(const T& buscado){
		Nodo* senialador = this->enejecucion;
		if (this->procesos == 1){
      if (senialador->activo){
				this->activos--;
			}

			delete senialador;
      this->enejecucion = NULL;
		}
		else{
			while (!(buscado == senialador->elem)){
			     senialador= senialador->siguiente;
			}

			if (senialador->activo){
				this->activos--;
			}

			if ((this->activos >0)&&(senialador->elem == this->enejecucion->elem)){
          ejecutarSiguienteProceso();
			}

			if ((this->activos == 0)&&(senialador->elem == this->enejecucion->elem)){
          this->enejecucion = this->enejecucion->siguiente;
			}

			senialador->siguiente->anterior = senialador->anterior;
			senialador->anterior->siguiente = senialador->siguiente;

			delete senialador;
		}

    this->procesos--;
	}

	template<typename T>
	void PlanificadorRR<T>::reanudarProceso(const T& buscado){
	int contador = this->procesos;
	Nodo* senialador = this->enejecucion;
	while (not(buscado == senialador->elem)){
		senialador= senialador->siguiente;
		contador--;
		}
	senialador->activo = true;
	if (this->activos == 0){
		this->enejecucion = senialador;
		}
	this->activos++;
	}

	template<typename T>
	void PlanificadorRR<T>::pausarProceso(const T& buscado){
	Nodo* puntero = this->enejecucion;
	while (puntero->elem != buscado){
		puntero = puntero->siguiente;
		}
	puntero->activo = false;
	this->activos--;
	if ((buscado == this->enejecucion->elem)&&(this->activos > 0)){
		this->ejecutarSiguienteProceso();
		}
	}
	template <typename T>
	void PlanificadorRR<T>::ejecutarSiguienteProceso(){

	Nodo* elquesigue = enejecucion->siguiente;
	while (elquesigue->activo != true){
			elquesigue = elquesigue->siguiente;
	}
	enejecucion = elquesigue;
}
	void detener();
	template <typename T>
	void PlanificadorRR<T>::detener(){
	this->interrupcion = true;
	}
	template <typename T>
	void PlanificadorRR<T>::reanudar(){
	this->interrupcion = false;
	}

	template <typename T>
	bool PlanificadorRR<T>::hayProcesos() const{
	if (this->procesos >0){
		return true;
	}
	else{
	return false;
	}
}

	template <typename T>
	bool PlanificadorRR<T>::hayProcesosActivos() const{
	return activos != 0;
	}

	template <typename T>
	int PlanificadorRR<T>::cantidadDeProcesos() const{
	return procesos;
	}

	template <typename T>
	int PlanificadorRR<T>::cantidadDeProcesosActivos() const{
	return activos;
	}

	template <typename T>
	const T& PlanificadorRR<T>::procesoEjecutado() const{
	return this->enejecucion->elem;
	}
/*
		bool buscarActivo (const PlanificadorRR<T>& planificador,const T& buscado)
	{
	int contador = planificador.procesos;
	Nodo* senialador = enejecucion;
	while (not( contador !=0 || buscado == senialador->elem)){
		senialador= senialador->siguiente;
		contador--;
		}
	return senialador->activo;
	}
*/
	template <typename T>
	bool PlanificadorRR<T>::estaActivo(const T& elem) const{
	int contador = this->procesos;
	Nodo* senialador = enejecucion;
	while (!(contador > 0) || (elem == senialador->elem)){
		senialador = senialador->siguiente;
	}

	return senialador->activo;
	}


	template <typename T>
	bool PlanificadorRR<T>::esPlanificado(const T& buscado) const{
	int contador = this->procesos;
	Nodo* senialador = enejecucion;
  //corregir esto urgente
	while ((buscado == senialador->elem) || (contador > 0)){

		if (buscado == senialador->elem){

			return true;
			}
		senialador= senialador->siguiente;
		contador--;
		}
	return false;
	}

	template <typename T>
	bool PlanificadorRR<T>::detenido() const{
	return interrupcion;
	}

	template<typename T>
	ostream& PlanificadorRR<T>::mostrarPlanificadorRR(ostream& flujo) const{
	flujo << "[";
	Nodo* puntero = this->enejecucion;
	for (int i = 0; i < this->procesos; i++){
		flujo << puntero->elem;
		if ((puntero->activo)&&(i==0)){
			flujo << "*";
		}
		if (not(puntero->activo)){
			flujo << " (i)";
		}
		if (i+1 < this->procesos){
			flujo << ", ";
		}
		puntero = puntero->siguiente;
	}
	flujo << "]";
	return flujo;
}

template <typename T>
bool PlanificadorRR<T>::operator==(const PlanificadorRR<T>& other) const{


	if ((interrupcion == other.interrupcion) && (procesos == other.procesos) && (activos == other.activos)){

		Nodo* senialadorother = other.enejecucion;
		Nodo* senialadorthis = this->enejecucion;
		int contador = other.procesos;
		for (int i = 0; i < contador; i++){
			if ((senialadorother->elem == senialadorthis->elem)&&(senialadorother->activo == senialadorthis->activo)){
				senialadorother = senialadorother->siguiente;
				senialadorthis = senialadorthis->siguiente;
			}
			else{
				return false;
			}
		}
		return true;
	}

return false;

}

template<class T>
ostream& operator<<(ostream& out, const PlanificadorRR<T>& a){
	return a.mostrarPlanificadorRR(out);
}
#endif // PLANIFICADOR_RR_H_
