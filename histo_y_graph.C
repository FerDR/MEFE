{
  gROOT->Reset(); //Reinicia las variables globales de ROOT
  gRandom->GetSeed(); //Obtiene una semilla para los numeros al azar
  
  Int_t n = 20;        //Tama#o de la muestra
  Int_t corridas = 1000; //Cantidad de series sinteticas a ser utilizadas/generadas
  double p = 0.5;
  Int_t escalaX=20; //Maximo valor del eje x y tambien la cantidad de bines
  
  TCanvas *ventana = new TCanvas("ventana","Experimento binomial y dist. teo."); //crea la ventana
  ventana->SetGrid();
  
  TH1F *histo = new TH1F("histo","Experimento binomial y dist. teo. (n=20, p=0.5)",escalaX+1,0-0.5,escalaX+0.5); //crea el histograma
  histo->SetFillColor(40);
  
  //Llena el histogrma
  for(Int_t j=0;j<corridas;j++){
    Int_t cuentas=0;
    
    for(Int_t i=0;i<n;i++){//este loop simula la tirada de las n monedas
      
      Double_t U0100=gRandom->Uniform(1); //genera un numero en [0,1] con dist uniforme
      if( U0100 <= p) cuentas++; //con una chance p de que sea cara
	
    }
    
    histo->Fill(cuentas);
  }
  
  histo->Draw(); //dibuja el histograma
  
  //Ahora vamos a calcular la distribucion teorica
  //y la vamos a graficar sobre la obtenida experimentalmente
  TGraph *gBinomial = new TGraph();//Creo un nuevo objeto TGraph
  for(int i=0;i<=n;i++){
    double probabilidad_de_i_caras = TMath::Binomial(n,i) * pow(p,i) * pow(1-p,n-i);
    
    gBinomial->SetPoint(i,i,corridas*probabilidad_de_i_caras);
  }
  
  gBinomial->Draw("p*l");
  
    
}
