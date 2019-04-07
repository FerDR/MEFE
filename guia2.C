int bernoulli(int n,double p){
	int exitos = 0;
	for(int i = 0; i < n; i++){
		double r11 = gRandom->Uniform(0,1);
		if(r11<p) exitos++;
	}
	return(exitos);
}

void guia2(){
	gROOT->Reset();
	gRandom->GetSeed();

	//Punto 1
	cout<<"Punto 1"<<endl;
	int n1 = 1000000;
	int bin[10];
	for(int i = 0; i<10;i++){
		bin[i] = 0;
		for(int j = 0; j < n1; j++){
			double r1 = gRandom->Uniform(0,1);
			if(r1<i/10.) bin[i] = bin[i] + 1;
		}
		cout << "P("<<i/10.<<") = "<<(bin[i] + 0.)/(n1 + 0.)<<endl;
	}
	
	//Punto 2
	int n2 = 1000;
	int puntos2 = 15;//no subir porque si no la teorica flashea
	cout<<"Punto 2"<<endl;
	TCanvas *c2 = new TCanvas("c2","Punto 2");
	c2->SetGrid();
	TH1F *h2 = new TH1F("h2","fotones detectados con 15 emitidos",2*puntos2+1,-0.25,puntos2+.25);
	h2->SetFillColor(40);	
	for(int i = 0; i < n2; i++){
		h2->Fill(bernoulli(15,0.75));
	}
	for(int i = 0; i < puntos2;i++){
		h2->SetBinError(i,sqrt(h2->GetBinContent(i)*(1-h2->GetBinContent(i)/n2)));
	}
	double norm2 = h2->GetEntries();
	h2->Scale(1/norm2);
	h2->Draw("HIST");
	TGraph *g2 = new TGraph();
	for(int i = 0; i < puntos2+1; i++){
		g2->SetPoint(i,i,TMath::Binomial(15,i) * pow(0.75,i) * pow(1-0.75,15-i));
	}
	g2->SetMarkerColor(kRed);
	g2->SetTitle("distribucion binomial");
	g2->Draw("same*l");
	if(h2->GetMaximum() + h2->GetBinError(h2->GetMaximumBin()) > TMath::MaxElement(puntos2,g2->GetY())){
		h2->SetAxisRange(0,h2->GetMaximum()*1.02+ h2->GetBinError(h2->GetMaximumBin())*1.02,"Y");
	}
	if(h2->GetMaximum() + h2->GetBinError(h2->GetMaximumBin()) < TMath::MaxElement(puntos2,g2->GetY())){
		h2->SetAxisRange(0,TMath::MaxElement(puntos2,g2->GetY())*1.02,"Y");
	}
	c2->BuildLegend();
	h2->Draw("SAME e1");
	c2->SaveAs("imagen2.png");

	//Punto 3
	cout<<"Punto 3"<<endl;
	int n3 = 1000;
	TCanvas *c3 = new TCanvas("c3","Punto 3");
	c3->SetGrid();
	int puntos3 = 35;
	TH1F *h3 = new TH1F("h3","fotones emitidos por segundo",2*puntos3+1,-0.25,puntos3+0.25);
	h3->SetFillColor(40);
	for (int i = 0; i < n3;i++){		
		h3->Fill(bernoulli(1000,15./1000.));
	}	
	for(int i = 0; i < puntos3;i++){
		h3->SetBinError(i,sqrt(h3->GetBinContent(i)));
	}
	double norm3 = h3->GetEntries();
	h3->Scale(1/norm3);
	h3->Draw("HIST");
	TGraph *g3= new TGraph();
	for(int i = 0; i < puntos3+1; i++){
		g3->SetPoint(i,i,TMath::Binomial(1000,i) * pow(15./1000.,i) * pow(1-15./1000.,1000-i));
	}
	g3->SetMarkerColor(kRed);
	g3->SetTitle("distribucion binomial");
	g3->Draw("same*l");
	TGraph *g35 = new TGraph();
	for (int i =0; i< puntos3 +1; i++){
		g35->SetPoint(i,i,TMath::Poisson(i,15));
	}
	g35->SetMarkerColor(kBlue);
	g35->SetTitle("distribucion poissoniana");
	g35->Draw("same*l");
	if(h3->GetMaximum() + h3->GetBinError(h3->GetMaximumBin()) > TMath::MaxElement(puntos3,g3->GetY())){
		h3->SetAxisRange(0,h3->GetMaximum()*1.03+ h3->GetBinError(h3->GetMaximumBin())*1.03,"Y");
	}
	if(h3->GetMaximum() + h3->GetBinError(h3->GetMaximumBin()) < TMath::MaxElement(puntos3,g3->GetY())){
		h3->SetAxisRange(0,TMath::MaxElement(puntos3,g3->GetY())*1.03,"Y");
	}
	c3->BuildLegend();
	h3->Draw("SAME e1");
	c3->SaveAs("imagen3.png");

	//Punto 4
	cout<<"Punto 4"<<endl;
	int n4 = 1000;
	TCanvas *c4 = new TCanvas("c4","Punto 4");
	c4->SetGrid();
	int puntos4 = 30;
	TH1F *h4 = new TH1F("h4","fotones detectados por segundo",2*puntos4+1,-0.25,puntos4+0.25);
	h4->SetFillColor(40);
	for (int i = 0; i < n4;i++){		
		h4->Fill(bernoulli(bernoulli(1000,15./1000.),0.75));
	}	
	for(int i = 0; i < puntos4;i++){
		h4->SetBinError(i,sqrt(h4->GetBinContent(i)));
	}
	double norm4 = h4->GetEntries();
	h4->Scale(1/norm4);
	h4->Draw("HIST");
	TGraph *g4 = new TGraph();
	for(int i = 0; i < puntos4 + 1; i++){
		double p4 = 0;
		for(int j = i; j<100;j++){
			p4 = p4+TMath::Binomial(j,i)*pow(0.75,i)*pow(1-0.75,j-i)*TMath::Poisson(j,15);
		}
		g4->SetPoint(i,i,p4);
	}
	g4->SetMarkerColor(kBlue);
	g4->SetTitle("distribucion compuesta");
	g4->Draw("same*l");
	if(h4->GetMaximum() + h4->GetBinError(h4->GetMaximumBin()) > TMath::MaxElement(puntos4,g4->GetY())){
		h4->SetAxisRange(0,h4->GetMaximum()*1.03+ h4->GetBinError(h4->GetMaximumBin())*1.03,"Y");
	}
	if(h4->GetMaximum() + h4->GetBinError(h4->GetMaximumBin()) < TMath::MaxElement(puntos4,g4->GetY())){
		h4->SetAxisRange(0,TMath::MaxElement(puntos4,g4->GetY())*1.03,"Y");
	}
	c4->BuildLegend();
	h4->Draw("SAME e1");
	c4->SaveAs("imagen4.png");

	//Punto 5
	cout<<"Punto 5"<<endl;
	int n5 = 1000;
	TCanvas *c5 = new TCanvas("c5","Punto 5");
	c5->SetGrid();
	int puntos5 = 30;
	TH1F *h5 = new TH1F("h5","fotones detectados por segundo",2*puntos5+1,-0.25,puntos5+0.25);
	h5->SetFillColor(40);
	for (int i = 0; i < n5; i++){
		h5->Fill(bernoulli(1000,15./1000.*0.75));
	}
	for(int i = 0; i < puntos5;i++){
		h5->SetBinError(i,sqrt(h5->GetBinContent(i)));
	}
	double norm5 = h5->GetEntries();
	h5->Scale(1/norm5);
	h5->Draw("HIST");
	TGraph *g5= new TGraph();
	for(int i = 0; i < puntos5; i++){
		g5->SetPoint(i,i,TMath::Binomial(1000,i) * pow(0.75*15./1000.,i) * pow(1-0.75*15./1000.,1000-i));
	}
	g5->SetMarkerColor(kRed);
	g5->SetTitle("distribucion binomial");
	g5->Draw("same*l");
	TGraph *g55 = new TGraph();
	for (int i =0; i< puntos5 +1; i++){
		g55->SetPoint(i,i,TMath::Poisson(i,15*0.75));
	}
	g55->SetMarkerColor(kBlue);
	g55->SetTitle("distribucion poissoniana");
	g55->Draw("same*l");
	if(h5->GetMaximum() + h5->GetBinError(h5->GetMaximumBin()) > TMath::MaxElement(puntos5,g5->GetY())){
		h5->SetAxisRange(0,h5->GetMaximum()*1.03+ h5->GetBinError(h5->GetMaximumBin())*1.03,"Y");
	}
	if(h5->GetMaximum() + h5->GetBinError(h5->GetMaximumBin()) < TMath::MaxElement(puntos5,g5->GetY())){
		h5->SetAxisRange(0,TMath::MaxElement(puntos5,g5->GetY())*1.03,"Y");
	}
	c5->BuildLegend();
	h5->Draw("SAME e1");
	c5->SaveAs("imagen5.png");
}

