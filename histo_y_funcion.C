void histo_y_funcion(){
  
  gROOT->Reset();
  gRandom->GetSeed();
  
  int n_bines = 100;
  int corridas = 1000;
  float rango_min=-10;
  float rango_max=10;
  float sigma = 1;
  float mu = 3;
  
  //crea la ventana, le define el color de fondo y hace que lo que se dibuje en ella tenga grilla
  TCanvas *c1 = new TCanvas("c1","Ejemplo de histograma y funcion",200,10,1000,600);
  c1->SetFillColor(42);
  c1->SetGrid();
  
  //crea el histograma y define el color de relleno
  TH1F *histo  = new TH1F("histo","Gaussiana",n_bines,rango_min,rango_max);
  histo->SetFillColor(45);
  
  //crea el objeto TF1 con la funcion a graficar. Pone nombre a los tres parametros y fifa sus valores
  TF1 *funcion_gauss = new TF1("funcion_gauss","[0]/(sqrt(2*3.14159)*[1])*TMath::Exp(-0.5*pow((x-[2])/[1],2))",rango_min,rango_max);
  funcion_gauss->SetParNames("normalizacion","sigma","media");
  funcion_gauss->SetParameter(0,corridas*(rango_max-rango_min)/n_bines);
  funcion_gauss->SetParameter(1,0.75);
  funcion_gauss->SetParameter(2,0);
  
  //llena el histograma con valores al azar generados con una distribucion Gauss(0,0.75)
  for(Int_t j=0;j<corridas;j++){
      histo->Fill(gRandom->Gaus(0,0.75));
  }
  
  //dibuja el histograma y la funcion
  histo->Draw();
  funcion_gauss->Draw("same");

}

