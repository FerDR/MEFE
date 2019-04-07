void g3p10(){
	gROOT->Reset();
	gRandom->GetSeed();
	//Metodo 1
	TCanvas *c1 = new TCanvas("c1","metodo 1");
	c1->SetGrid();
	TH1F *h1 = new TH1F("h1","Cauchy",101,-20.25,20.25);
	h1->SetFillColor(17);
	
	for (int i = 0; i < 10000; i++){
		double theta = gRandom->Uniform(3.1415926);
		h1->Fill(sin(theta-3.1415926/2)/cos(theta-3.1415926/2));
	}
	double norm1 = h1->GetEntries();
	for (int i = 0; i < 101; i++){
		h1->SetBinError(i,sqrt(h1->GetBinContent(i)*(1-h1->GetBinContent(i)/norm1)));
	}

	h1->Scale(1/norm1/40.5*101);
	h1->Draw("HIST");
	TGraph *g1 = new TGraph();
	
	for(int i = 0; i < 100; i++){
		g1->SetPoint(i,i-50,1/3.1415926/(1+pow(i-50,2)));
	}
	g1->SetMarkerColor(kRed);
	g1->SetTitle("distribucion de Cauchy");
	g1->Draw("same*l");
	h1->SetAxisRange(0,0.35,"Y");
	c1->BuildLegend();
	h1->Draw("same e1");
	c1->SaveAs("imagen1.png");

	//----------------------------Metodo 2-------------------------------------
	double a = -20;
	double b = 20;
	double max = 1/3.1415926;
	TCanvas *c2 = new TCanvas("c2","MC");
	c2->SetGrid();
	TH1F *h2 = new TH1F("h2","Monte Carlo",101,-20.25,20.25);
	h2->SetFillColor(68);

	while(h2->GetEntries()<10000){
		double x2 = gRandom->Uniform(1);
		double y2 = gRandom->Uniform(1);
		double u = a+(b-a)*x2;
		double v = max*y2;
		if(v<1/3.1415926/(1+pow(u,2))){
			h2->Fill(u);
		}
	}

	double norm2 = h2->GetEntries();
	for (int i = 0; i < 101; i++){
		h2->SetBinError(i,sqrt(h2->GetBinContent(i)*(1-h2->GetBinContent(i)/norm2)));
	}
	h2->Scale(1/norm2/40.5*101);
	h2->Draw("HIST");
	TGraph *g2 = new TGraph();
	
	for(int i = 0; i < 100; i++){
		g2->SetPoint(i,i-50,1/3.1415926/(1+pow(i-50,2)));
	}
	g2->SetMarkerColor(kRed);
	g2->SetTitle("distribucion de Cauchy");
	g2->Draw("same*l");
	h2->SetAxisRange(0,0.35,"Y");
	c2->BuildLegend();
	h2->Draw("same e1");
	c2->SaveAs("imagen2.png");	
}