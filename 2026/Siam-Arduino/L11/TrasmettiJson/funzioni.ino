/*
Funzione che legge i dati del sensore di temp...
*/
int readSensor(){ //la funzione restituisce un intero (int)
  //creo una variabile interna alla funzione
  int n = 0; 
  //simulo il sensore con dei numeri casuali
  n = 20 + random(0,10);
  //restituisco il valore di n
  return n;
}