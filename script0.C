{
    gROOT->Reset(); //Reinicia las variables globales de ROOT
    gRandom->GetSeed(); //Obtiene una semilla para los numeros al azar
    
    Int_t corridas=1000;    //Tama#o de la muestra
    Double_t p=0.3;  //Valor de p
    
    Int_t n_0p=0; //Con esta variable vamos a contar el numero de eventos en [0,p]
    
    for(Int_t i=0;i<corridas;i++){
      Double_t U01 = gRandom->Uniform(0,1);//genera un numero al azar a partir de una distribucion uniforme en [0,1]
      if(U01<=p) n_0p++; //si U01 esta entre 0 y p incrementa el contador n_0p en uno.
    }

    cout << "\n\np = " << p << endl;
    cout << "U[0,1] cayo entre 0 y p el " << (Double_t)n_0p/corridas <<" de las veces\n\n";
    
}
