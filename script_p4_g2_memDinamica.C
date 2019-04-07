void script_p4_g2_memDinamica(){ //El nombre de la fincion principal tiene que ser igual al del archivo .C
    gROOT->Reset();
    gRandom->GetSeed();
    
    Int_t n=500;        //Tama#o de la muestra
    Int_t corridas=3000; //Cantidad de series sinteticas a ser utilizadas/generadas
    Int_t escalaX=50; //Maximo valor del eje x y tambien la cantidad de bines

    TCanvas *ventana = new TCanvas("ventana","Problema 2 - Guia 4",200,10,1000,600); //crea la ventana en forma dinamica
    ventana->SetGrid();
        
    TH1F *histo = new TH1F("histo","Problema 2 - Guia 4",escalaX,0,escalaX); //crea el histograma en forma dinamica
    histo->SetFillColor(45);

    //Llena el histogrma
    for(Int_t j=0;j<corridas;j++){
        Int_t cuentas=0;
        
        for(Int_t i=0;i<n;i++){//este loop simula el resultado de una encuesta
          
          Double_t U0100=gRandom->Uniform(100); //genera un numero en [0,100] con dist uniforme
          if( U0100 <= 1) cuentas++; //con una chance del 1% incrementa cuentas
          
        }
        
        histo->Fill(cuentas);
    }

    histo->Draw(); //dibuja el histograma
    
    //Ahora vamos a ver si reobtenemos "experimentalmente" el resultado del problema 2.4
    Double_t nSobre10=0; //aca vamos a guardar la cantidad de veces que la encuesta dio 2% o mas
    for(int i=11;i<escalaX;i++){
      nSobre10 = nSobre10 + histo->GetBinContent(i);
    }
    cout <<"\nP(n>=10): "<<nSobre10/corridas<<endl<<endl;
}

