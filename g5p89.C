double suma(double x[],int n){
	double sumado = 0; 
	for (int i = 0; i < n; i++){
		sumado = sumado + x[i];
	}
	return sumado;
}

double suma2(double x[], double y[],int n){
	double sumado = 0;
	for (int i = 0; i < n; i++){
		sumado = sumado +x[i]*y[i];
	}
	return sumado;
}

void g5p89(){
	gROOT->Reset();
	double x [11] = {2.,2.1,2.2,2.3,2.4,2.5,2.6,2.7,2.8,2.9,3.};
	double y [11] = {2.78,3.29,3.29,3.33,3.23,3.69,3.46,3.87,3.62,3.40,3.99};
	double yerr [11] = {0.3,0.3,0.3,0.3,0.3,0.3,0.3,0.3,0.3,0.3,0.3};
	double ex [11] = {0,0,0,0,0,0,0,0,0,0,0};
	//p8

	double delta = 11*suma2(x,x,11)-pow(suma(x,11),2);

	double b = (suma2(x,x,11)*suma(y,11)-suma(x,11)*suma2(x,y,11))/delta;

	double a = (11*suma2(x,y,11)-suma(x,11)*suma(y,11))/delta;

	double varb = suma2(x,x,11)*0.3*0.3/delta;

	double vara = 11*0.3*0.3/delta;

	double cov = -suma(x,11)*0.3*0.3/delta;
	
	TCanvas *c1 = new TCanvas("c1","Data",200,10,700,500);
   	c1->SetFillColor(27);
   	c1->SetGrid();
   	c1->GetFrame()->SetFillColor(15);
   	c1->GetFrame()->SetBorderSize(12);
   	

	TGraphErrors *graf = new TGraphErrors(11,x,y,ex,yerr);
	graf->SetTitle("datos con su ajuste");
	graf->SetMarkerColor(4);
   	graf->SetMarkerStyle(21);
	graf->Draw("AP");

	TPaveLabel *pl = new TPaveLabel(-2.722343,6.44797,1.572668,6.937022,"New Title","br");
   	pl->Draw();

	double ynew[11];
	for (int i = 0; i < 11; i++){
		ynew[i] = a*x[i]+b;
	}
	TGraphErrors *fit = new TGraphErrors(11,x,ynew,ex,ex);
	fit->SetTitle("ajuste");
	fit->SetLineColor(82);
	fit->Draw("same");
	//de aca hasta la linea 88 es para la leyenda
	TLegend *leg1 = new TLegend(0.1131805,0.6561181,0.4140401,0.8670886,NULL,"brNDC");
   leg1->SetBorderSize(1);
   leg1->SetLineColor(1);
   leg1->SetLineStyle(1);
   leg1->SetLineWidth(1);
   leg1->SetFillColor(0);
   leg1->SetFillStyle(1001);
   TLegendEntry *entry1=leg1->AddEntry("Graph0","datos","lpf");
   entry1->SetFillStyle(1000);
   entry1->SetLineColor(1);
   entry1->SetLineStyle(1);
   entry1->SetLineWidth(1);
   entry1->SetMarkerColor(4);
   entry1->SetMarkerStyle(21);
   entry1->SetMarkerSize(1);
   entry1->SetTextFont(42);
   entry1=leg1->AddEntry("Graph1","ajuste","lpflpf");
   entry1->SetFillStyle(1000);
   entry1->SetLineColor(82);
   entry1->SetLineStyle(1);
   entry1->SetLineWidth(1);
   entry1->SetMarkerColor(1);
   entry1->SetMarkerStyle(1);
   entry1->SetMarkerSize(1);
   entry1->SetTextFont(42);
   leg1->Draw();

	c1->SaveAs("imagen1.png");

	//--------------------parte 2-------------------------------------------------------------
	double x2[50];
	for (int i = 0; i<50; i++){
		x2[i] = i*0.1;
	}

	double y2[50];
	for (int i = 0; i < 50; i++){
		y2[i] = a*x2[i]+b;
	}
	double xerr2[50];
	for (int i = 0; i < 50; i++){
		xerr2[i] = 0;
	}

	double err2[50];
	for(int i = 0; i < 50; i++){
		err2[i] = pow(x2[i]*x2[i]*vara+varb+2*x2[i]*cov,0.5);
		
	}

	double err3[50];
	for (int i =0; i < 50; i++){
		err3[i] = pow(x2[i]*x2[i]*vara+varb,0.5);
	}

	TCanvas *c2 = new TCanvas("c2","Data2",200,10,700,500);
   	c2->SetFillColor(45);
   	c2->SetGrid();
   	c2->GetFrame()->SetFillColor(15);
   	c2->GetFrame()->SetBorderSize(12);

	TGraphErrors *g2 = new TGraphErrors(50,x2,y2,xerr2,err2);
	g2->SetLineColor(63);
	

	TGraphErrors *g3 = new TGraphErrors(50,x2,y2,xerr2,err3);
	g3->SetLineColor(82);
	g3->SetTitle("propagacion correcta e incorrecta");
	g3->Draw();
	graf->Draw("SAME");
	g2->Draw("SAME");
	//de aca a la linea 169 es leyenda
	TLegend *leg2 = new TLegend(0.1260745,0.6160338,0.4269341,0.8270042,NULL,"brNDC");
   leg2->SetBorderSize(1);
   leg2->SetLineColor(1);
   leg2->SetLineStyle(1);
   leg2->SetLineWidth(1);
   leg2->SetFillColor(0);
   leg2->SetFillStyle(1001);
   TLegendEntry *entry2=leg2->AddEntry("Graph0","error incorrecto","lpf");
   entry2->SetFillStyle(1000);
   entry2->SetLineColor(82);
   entry2->SetLineStyle(1);
   entry2->SetLineWidth(1);
   entry2->SetMarkerColor(1);
   entry2->SetMarkerStyle(1);
   entry2->SetMarkerSize(1);
   entry2->SetTextFont(42);
   entry2=leg2->AddEntry("Graph1","datos","lpflpf");
   entry2->SetFillStyle(1000);
   entry2->SetLineColor(1);
   entry2->SetLineStyle(1);
   entry2->SetLineWidth(1);
   entry2->SetMarkerColor(4);
   entry2->SetMarkerStyle(21);
   entry2->SetMarkerSize(1);
   entry2->SetTextFont(42);
   entry2=leg2->AddEntry("Graph2","error correcto","lpflpflpf");
   entry2->SetFillStyle(1000);
   entry2->SetLineColor(63);
   entry2->SetLineStyle(1);
   entry2->SetLineWidth(1);
   entry2->SetMarkerColor(1);
   entry2->SetMarkerStyle(1);
   entry2->SetMarkerSize(1);
   entry2->SetTextFont(42);
   leg2->Draw();
 
	c2->SaveAs("imagen2.png");

	//-------------------parte 3-------------------------------------------------------------
	double y3[11];
	TH1F *h1 = new TH1F("h1","distribucion de y(0.5)",50,-0.5,4.5);
	TCanvas *c3 = new TCanvas("c3","punto 4",200,10,700,500);
	c3->SetGrid();
	for (int j = 0; j < 10000; j++){
		for (int i = 0; i < 11; i++){
			y3[i] = gRandom->Gaus(b+a*x[i],0.3);
		}	
		double b2 = (suma2(x,x,11)*suma(y3,11)-suma(x,11)*suma2(x,y3,11))/delta;

		double a2 = (11*suma2(x,y3,11)-suma(x,11)*suma(y3,11))/delta;

		h1->Fill(a2*0.5+b2);
	}
	double norm = h1->GetEntries();
	for (int i = 0; i < 50; i++){
		h1->SetBinError(i,sqrt(h1->GetBinContent(i)*(1-h1->GetBinContent(i)/norm)));
	}
	
	h1->Scale(1/norm/5*50);
	h1->Draw("HIST");
	

	double exp = a*0.5+b;
	double sigmabien = err2[6];
	double sigmamal =  err3[6];

	TGraph *g4 = new TGraph();
	for (int i = 0; i < 50; i++){
		g4->SetPoint(i,i/10.-0.5,1/pow(2*3.1415926,0.5)/sigmabien*pow(2.71828,-1/2.*pow((i/10.-0.5-exp)/sigmabien,2)));
	}
	g4->SetLineColor(45);
	g4->SetTitle("sigma correcto");
	g4->Draw("SAME");

	TGraph *g5 = new TGraph();
	for (int i = 0; i < 50; i++){
		g5->SetPoint(i,i/10.-0.5,1/pow(2*3.1415926,0.5)/sigmamal*pow(2.71828,-1/2.*pow((i/10.-0.5-exp)/sigmamal,2)));
	}
	g5->SetTitle("sigma erroneo");
	g5->SetLineColor(82);
	g5->Draw("SAME");
	//de aca hasta la linea 252 es para que arme la leyenda
	TLegend *leg = new TLegend(0.6502933,0.4845361,0.9501466,0.6936672,NULL,"brNDC");
   leg->SetBorderSize(1);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("h1","distribucion de y(0.5)","lpf");
   entry->SetFillStyle(1001);
   int ci = TColor::GetColor("#000099");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(1);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("","sigma correcto","lpflpf");
   entry->SetFillStyle(1000);
   entry->SetLineColor(45);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(1);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("","sigma erroneo","lpflpflpf");
   entry->SetFillStyle(1000);
   entry->SetLineColor(82);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(1);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   leg->Draw();

	h1->Draw("SAME e1");
	c3->SaveAs("imagen3.png");
}