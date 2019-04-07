void g3e9(){
	gROOT->Reset();
	double rango_min = -12;
	double rango_max = 12;
	TCanvas *c1 = new TCanvas("c1","gauss y cauchy");
	c1->SetGrid();
	TF1 *funcion_gauss = new TF1("funcion_gauss","[0]/(sqrt(2*3.14159)*[1])*TMath::Exp(-0.5*pow((x-[2])/[1],2))",rango_min,rango_max);
	funcion_gauss->SetParameter(0,1/3.14159*sqrt(2*3.14159)*0.75);
  	funcion_gauss->SetParameter(1,0.75);
  	funcion_gauss->SetParameter(2,0);
  	funcion_gauss->SetLineColor(45);
  	TF1 *funcion_cauchy = new TF1("funcion_cauchy","1/3.14159/(1+pow(x,2))",rango_min,rango_max);
  	TF1 *colas = new TF1("colas","[0]/(sqrt(2*3.14159)*[1])*TMath::Exp(-0.5*pow((x-[2])/[1],2))+[3]/(sqrt(2*3.14159)*[4])*TMath::Exp(-0.5*pow((x-[5])/[4],2))",rango_min,rango_max);
  	colas->SetParameter(0,1./2/1.0444);
  	colas->SetParameter(1,0.75);
  	colas->SetParameter(2,0);
  	colas->SetParameter(3,1./2/1.0444);
  	colas->SetParameter(4,3);
  	colas->SetParameter(5,0);
  	colas->SetParameter(6,100);
  	colas->SetLineColor(83);
  	funcion_gauss->Draw();
  	funcion_cauchy->Draw("same");
  	colas->Draw("same");
  	c1->BuildLegend();
}