//de aca hasta la linea 37 es para calcular la distribucion del estadistico de kolmogorov,
//sacado de "Evaluating Kolmogorov's distribution", Marsaglia, Tsang y Wang, 2003
void mMultiply(double *A,double *B,double *C,int m)
{ int i,j,k; double s;
for(i=0;i<m;i++) for(j=0; j<m; j++)
{s=0.; for(k=0;k<m;k++) s+=A[i*m+k]*B[k*m+j]; C[i*m+j]=s;}
}
void mPower(double *A,int eA,double *V,int *eV,int m,int n)
{ double *B;int eB,i;
if(n==1) {for(i=0;i<m*m;i++) V[i]=A[i];*eV=eA; return;}
mPower(A,eA,V,eV,m,n/2);
B=(double*)malloc((m*m)*sizeof(double));
mMultiply(V,V,B,m); eB=2*(*eV);
if(n%2==0){for(i=0;i<m*m;i++) V[i]=B[i]; *eV=eB;}
else {mMultiply(A,B,V,m); *eV=eA+eB;}
if(V[(m/2)*m+(m/2)]>1e140) {for(i=0;i<m*m;i++) V[i]=V[i]*1e-140;*eV+=140;}
free(B);
}
double K(int n,double d)
{ int k,m,i,j,g,eH,eQ;
double h,s,*H,*Q;
//OMIT NEXT LINE IF YOU REQUIRE >7 DIGIT ACCURACY IN THE RIGHT TAIL
//s=d*d*n; if(s>7.24||(s>3.76&&n>99)) return 1-2*exp(-(2.000071+.331/sqrt(n)+1.409/n)*s);
k=(int)(n*d)+1; m=2*k-1; h=k-n*d;
H=(double*)malloc((m*m)*sizeof(double));
Q=(double*)malloc((m*m)*sizeof(double));
for(i=0;i<m;i++) for(j=0;j<m;j++)
if(i-j+1<0) H[i*m+j]=0; else H[i*m+j]=1;
for(i=0;i<m;i++) {H[i*m]-=pow(h,i+1); H[(m-1)*m+i]-=pow(h,(m-i));}
H[(m-1)*m]+=(2*h-1>0?pow(2*h-1,m):0);
for(i=0;i<m;i++) for(j=0;j<m;j++)
if(i-j+1>0) for(g=1;g<=i-j+1;g++) H[i*m+j]/=g;
eH=0; mPower(H,eH,Q,&eQ,m,n);
s=Q[(k-1)*m+k-1];
for(i=1;i<=n;i++) {s=s*i/n; if(s<1e-140) {s*=1e140; eQ-=140;}}
s*=pow(10.,eQ); free(H); free(Q); return s;
}
double G(double x){//da la integral de la normal(0,1) desde 0 hasta x
	double g = 0;
	for(int i = 0; i < 10000; i++){
		g = g + pow(2*3.1415926,-0.5)*pow(2.71828,-0.5*pow(x*i/10000.,2))*x/10000.;
	}
	return g;
}
int factorial(int x){//creo que el nombre la explica
	int f = 1;
	for(int i = x; i > 0; i = i-1){
		f = f*i;
	}
	return f;
}
void final(){
	gROOT->Reset();
	//Patentes adquiridas en la esquina de Gana y Juan B Justo, en el limite entre los barrios portenios Versalles y Liniers
	int MyList[101] = {95679,110745,195082,200077,234861,246743,246749,277287,308610,347295,358757,386486,390997,407211,419687,459949,472659,491537,520096,550306,556960,559986,605429,632289,632399,632431,714935,747573,757507,764653,782061,789460,804758,928419,935220,980894,981134,988869,1049993,1097191,1139906,1178961,1183983,1247720,1268559,1313828,1337522,1358782,1390825,1391623,1400134,1433339,1475248,1479594,1499014,1522768,1528450,1537852,1569246,1592040,1600831,1657482,1681060,1699393,1740249,1792463,1809401,1809426,1835458,1863555,1875888,1876235,1876285,1885631,1888929,1902309,1914772,1917679,1950674,1969203,1999431,2005264,2013739,2033133,2033980,2049824,2097443,2119546,2163570,2164535,2200415,2238712,2272288,2274616,2305305,2350362,2350389,2359855,2362359,2375622,2377519};
//------------------------------PUNTO 3--------------------------------------------------------------
	//hay muchas lineas comentadas que arrancan con cout<<, son para debugueo y no tendrian incidencia alguna aunque no estuvieran comentadas
	TCanvas *p3 = new TCanvas("c1","punto 3",200,10,700,500);
	p3->SetGrid();

	double teorica[301];//genera un array, NO es elemento que grafico, pero con el grafico no puedo (no se) hacer cuentas
	for(int i = 0; i < 301; i++){
		teorica[i] = i/300.;
	}

	double empirica[301];
	empirica[0] = 0;
	for(int i = 1; i < 300; i++){
		for (int j = 0; j < 100; j++){
				if(i*2428509./300 >= MyList[j-1]){
					if(i*2428509./300 < MyList[j])empirica[i] = j/101.;
				}
			}
	}
	empirica[294] = 1;//este indice viene porque 294/300*2428509 es mayor a la ultima que vi
	empirica[295] = 1;
	empirica[296] = 1;
	empirica[297] = 1;
	empirica[298] = 1;
	empirica[299] = 1;
	empirica[300] = 1;
	
	TGraph *teo = new TGraph();//este si es el que se grafica
	for (int i = 0; i < 301; i++){
		teo->SetPoint(i,i*2428509./300,teorica[i]);
	}
	teo->SetLineColor(45);
	teo->Draw();

	TGraph *emp = new TGraph();
	for (int i = 0; i < 300; i++){
		emp->SetPoint(i,i*2428509./300,empirica[i]);
	}
	emp->SetPoint(300,2428509,1);
	emp->SetLineColor(65);
	emp->Draw("same");
	
	double diferencia[301];
	for(int i = 0; i<301; i++){
		diferencia[i] = abs(teorica[i]-empirica[i]);
	}
	double kolmo = 0;
	int PosicionKolmo;
	for(int i = 0; i < 301; i++){
		if (diferencia[i] > kolmo) {
			kolmo = diferencia[i];
			PosicionKolmo = i;
		}
	}
	TGraph *kolm = new TGraph();//dibuja una linea para marcar el valor medido
	for (int i = 0; i < 15; i++){
		kolm->SetPoint(i,PosicionKolmo*2428509./300,i*(teorica[PosicionKolmo]-empirica[PosicionKolmo])/14+empirica[PosicionKolmo]);
	}
	kolm->SetLineColor(94);
	kolm->Draw("SAME");
	cout<<"el kolmo para uniforme dio "<<kolmo<<", su p-valor es "<<1-K(101,kolmo);

	//todas las secciones tienen un bloque casi identico a este al final, pone nombre al grafico, los ejes y la leyenda y guarda la imagen
	teo->SetTitle("Test de Kolmogorov con una uniforme");//Se llama asi porque no puedo lograr que el nombre del grafico NO sea el nombre de lo primero que grafica
	teo->GetXaxis()->SetTitle("Patente");//lo mismo vale para los ejes, se los pone al primer elemento pero quedan para todo el grafico
	teo->GetYaxis()->SetTitle("Probabilidad cumulativa");
	teo->GetXaxis()->CenterTitle();
	teo->GetYaxis()->CenterTitle();
	TLegend *leg1 = new TLegend(0.15,0.55,.5,.85);
	leg1->AddEntry(teo,"Distribucion cumulativa teorica","l");
	leg1->AddEntry(emp,"Distribucion cumulativa experimental","l");
	leg1->AddEntry(kolm,"Estadistico de Kolmogorov","l");
	leg1->Draw("SAME");
	p3->SaveAs("imagen1.png");
	//---------------------------Punto 3b-----------------------------------------
	TCanvas *punto3b = new TCanvas("c2","punto 3b",200,10,700,500);
	punto3b->SetGrid();
	double teorica2[301];
	for(int i = 0; i < 301; i++){
		teorica2[i] = (1-pow(2.71828,-4*pow(10,-7)*i*2428509./300))/(1-pow(2.71828,-4*pow(10,-7)*2428509));
	}
	TGraph *teo2 = new TGraph();
	for (int i = 0; i < 301; i++){
		teo2->SetPoint(i,i*2428509./300,teorica2[i]);
	}
	teo2->SetLineColor(45);
	
	emp->Draw();
	teo2->Draw("SAME");

	double diferencia2[301];
	for(int i = 0; i<301; i++){
		diferencia2[i] = abs(teorica2[i]-empirica[i]);
	}
	double kolmo2 = 0;
	int PosicionKolmo2;
	for(int i = 0; i < 301; i++){
		if (diferencia2[i] > kolmo2) {
			kolmo2 = diferencia2[i];
			PosicionKolmo2 = i;
		}
	}
	TGraph *kolm2 = new TGraph();
	for (int i = 0; i < 15; i++){
		kolm2->SetPoint(i,PosicionKolmo2*2428509./300,i*(teorica2[PosicionKolmo2]-empirica[PosicionKolmo2])/14+empirica[PosicionKolmo2]);
	}
	kolm2->SetLineColor(94);
	kolm2->Draw("SAME");
	cout<<endl<<"el kolmo para exponencial dio "<<kolmo2<<", su p-valor es "<<1-K(101,kolmo2)<<endl;

	emp->SetTitle("Test de Kolmogorov con una exponencial");
	emp->GetXaxis()->SetTitle("Patente");
	emp->GetYaxis()->SetTitle("Probabilidad cumulativa");
	emp->GetXaxis()->CenterTitle();
	emp->GetYaxis()->CenterTitle();
	TLegend *leg2 = new TLegend(0.1361032,0.6730361,0.4985673,0.8556263);
	leg2->AddEntry(teo2,"Distribucion cumulativa teorica exponencial","l");
	leg2->AddEntry(emp,"Distribucion cumulativa experimental","l");
	leg2->AddEntry(kolm2,"Estadistico de Kolmogorov","l");
	leg2->Draw("SAME");
	punto3b->SaveAs("imagen2.png");


	//-------Ploteo de los pvalores y la significancia
	TCanvas *c25 = new TCanvas("c25","pvalores",200,10,700,500);
	c25->SetGrid();
	TGraph *denskolmo = new TGraph();
	for(int i = 0; i < 50; i++){
		denskolmo->SetPoint(i,i/200.,(K(101,(i+1)/200.)-K(101,i/200.))*200);
	}
	denskolmo->Draw();
	//plotea las 3 lineas rectas, no las puse hasta la altura de la curva porque si no la ultima no se ve
	TGraph *PV1 = new TGraph();//pvalor1
	TGraph *PV2 = new TGraph();//pvalor2
	TGraph *sig = new TGraph();//significancia
	PV1->SetPoint(0,kolmo,0);
	PV2->SetPoint(0,kolmo2,0);
	sig->SetPoint(0,1.35810/pow(101.,0.5),0);
	PV1->SetPoint(1,kolmo,1.07*(K(101,kolmo+1/100.)-K(101,kolmo))*100);
	PV2->SetPoint(1,kolmo2,2);
	sig->SetPoint(1,1.35810/pow(101.,0.5),1.1*(K(101,1.35810/pow(101.,0.5)+1/100.)-K(101,1.35810/pow(101.,0.5)))*100);
	PV1->SetLineColor(45);
	PV2->SetLineColor(65);
	sig->SetLineColor(85);
	PV1->Draw("SAME");
	PV2->Draw("SAME");
	sig->Draw("SAME");

	denskolmo->SetTitle("Densidad de probabilidad de Kolmogorov, p-valores y significancia");
	denskolmo->GetXaxis()->SetTitle("Estadistico de Kolmogorov");
	denskolmo->GetYaxis()->SetTitle("Densidad de probabilidad");
	denskolmo->GetXaxis()->CenterTitle();
	denskolmo->GetYaxis()->CenterTitle();
	TLegend *leg25 = new TLegend(.4,.6,.85,.85);
	leg25->AddEntry(denskolmo,"Densidad de probabilidad","l");
	leg25->AddEntry(PV1,"Estadistico de la uniforme","l");
	leg25->AddEntry(PV2,"Estadistico de la exponencial","l");
	leg25->AddEntry(sig,"valor critico","l");
	leg25->Draw("SAME");
	c25->SaveAs("imagen25.png");

	//--------------Potencia------------------
	double simulexp[101];
	int Nbins = 100;
	int k3;//el nombre kolmotrucho no es buena nomenclatura pero es la que use en ese momento para referirme a que es un estadistico de kolmogorov cuya distribucion NO es la del estadistico de kolmogorov
	TH1F *kolmotrucho = new TH1F("h1","distribucion del estadistico de kolmogorov con datos provenientes de H1",Nbins,0,0.5);//las t en las variables de esta seccion son abreviacion de trucho
	for(int i = 0; i< 50000; i++){
		k3 = 0;
		for(int j = 0; k3 < 101; j++){
			int a = gRandom->Exp(0.25*pow(10,7));
			if (a <= 2428509) {
				simulexp[k3] = a;
				k3++;
			}
		}
		sort(simulexp,simulexp+101);
		//for(int j = 0; j < 101; j++) cout<<simulexp[j]<<endl;
		double empiricat[301];
		empiricat[0] = 0;
		for(int l = 1; l < 300; l++){
			for (int j = 0; j < 100; j++){
					if(l*2428509./300 >= simulexp[j-1]){
						if(l*2428509./300 < simulexp[j])empiricat[l] = j/101.;
					}
				}
		}
		//cout<<simulexp[100]<<endl;
		for(int l = 50; l < 301; l++){
			if (empiricat[l] < 0.0001)empiricat[l] = 1;
		}
		//for(int l = 0; l < 300; l++)cout<<empiricat[l]<<endl;
		double diferenciat[301];
		for(int l = 0; l<301; l++){
			diferenciat[l] = abs(teorica[l]-empiricat[l]);
			//cout<<teorica[300]<<"  "<<empiricat[300]<<endl;
		}
		double kolmot = 0;
		for(int l = 0; l < 301; l++){
			if (diferenciat[l] > kolmot) kolmot = diferenciat[l];
		}
		//cout<<kolmot<<endl;
		kolmotrucho->Fill(kolmot);
	}
	TCanvas *power = new TCanvas("c3","potencia",200,10,700,500);
	power->SetGrid();
	double norm = kolmotrucho->GetEntries();//normalizacion del histograma
	kolmotrucho->Scale(1/norm*Nbins/0.5);//1/(numero_de_entradas)*(numero_de_bins)/(ancho_del_histograma)
	
	TGraph *distkolmo = new TGraph();
	for(int i = 0; i < 50; i++){
		distkolmo->SetPoint(i,i/100.,(K(101,(i+1)/100.)-K(101,i/100.))*100);
	}
	distkolmo->Draw();
	kolmotrucho->Draw("HISTsame");

	double kcrit= 1.35810/pow(101.,0.5);//aproximacion para significancia 0.05
	double aux = kcrit/(0.5/Nbins);
	int bincrit = aux+1;//como esta discretizado tengo que ver en que bin queda el kcritico
	//cout<<kcrit<<"  "<<bincrit<<"  "<<kolmotrucho->GetBinContent(bincrit)<<endl;
	TGraph *kolmcrit = new TGraph();
	for (int i = 0; i < 15; i++){
		kolmcrit->SetPoint(i,kcrit,i/14.*kolmotrucho->GetBinContent(bincrit));
	}
	kolmcrit->SetLineColor(85);
	kolmcrit->Draw("same");
	
	double potencia;
	for(int i = 0; i < 100; i++){
		if (i*0.5/100.>kcrit) potencia = potencia + kolmotrucho->GetBinContent(i);
	}
	potencia = potencia/Nbins*0.5;
	cout<<"la potencia es "<<potencia<<endl;

	distkolmo->SetTitle("potencia del test de Kolmogorov para uniforme vs. exponencial");
	distkolmo->GetXaxis()->SetTitle("Estadistico de Kolmogorov");
	distkolmo->GetYaxis()->SetTitle("Densidad de probabilidad");
	distkolmo->GetXaxis()->CenterTitle();
	distkolmo->GetYaxis()->CenterTitle();
	TLegend *leg3 = new TLegend(0.2495702,0.5732484,0.8409742,0.9026115);
	leg3->AddEntry(distkolmo,"distribucion del estadistico de Kolmogorov si la hipotesis nula es valida","l");
	leg3->AddEntry(kolmotrucho,"distribucion del estadistico de Kolmogorov si los datos provienen de una exponencial","l");
	leg3->AddEntry(kolmcrit,"valor critico del estadistico para significancia 0.05","l");
	leg3->Draw("SAME");
	power->SaveAs("imagen3.png");
	//aca quise ver que pasaba si hacia kolmogorov con una exponencial de parametro de maxima verosimilitud pero...
	/*Por lo que dice en el Frodessen Kolmogorov no vale si un parametro de la funcion viene de tus datos, de todos modos tampoco superaba el test
	//-----------------------------------Punto 3c-----------------------------------
	TCanvas *punto3c = new TCanvas("c3","punto 3c",200,10,700,500);
	punto3c->SetGrid();

	double promedio = 0.;
	for(int i = 0; i < 101; i++){
		promedio = promedio + MyList[i];
	}
	promedio = promedio/101.;

	double teorica3[301];
	for(int i = 0; i < 301; i++){
		teorica3[i] = 1-pow(2.71828,-1/promedio*i*2377519./300.);
	}
	TGraph *teo3 = new TGraph();
	for (int i = 0; i < 301; i++){
		teo3->SetPoint(i,i*2377519./300,teorica3[i]);
	}
	teo3->SetLineColor(45);
	
	emp->Draw();
	teo3->Draw("SAME");

	double diferencia3[301];
	for(int i = 0; i<301; i++){
		diferencia3[i] = abs(teorica3[i]-empirica[i]);
	}
	double kolmo3 = 0.;
	int PosicionKolmo3;
	for(int i = 0; i < 301; i++){
		if (diferencia3[i] > kolmo3) {
			kolmo3 = diferencia3[i];
			PosicionKolmo3 = i;
		}
	}
	TGraph *kolm3 = new TGraph();
	for (int i = 0; i < 15; i++){
		kolm3->SetPoint(i,PosicionKolmo3*2377519./300,i*(teorica3[PosicionKolmo3]-empirica[PosicionKolmo3])/14+empirica[PosicionKolmo3]);
	}
	kolm3->SetLineColor(94);
	kolm3->Draw("SAME");
	cout<<endl<<"el kolmo para exponencial con lambda "<<1./promedio<< " dio "<<kolmo3<<", su p-valor es "<<1-K(101,kolmo3)<<endl;	

	*/
	//-----------------------------------------------------------Punto 4----------------------------------------------
	TCanvas *c8 = new TCanvas("c8","punto 4",200,10,700,500);//la nomenclatura fea (c8) viene del hecho de que los hice en desorden y ya me perdi con que nombres de variables ya use
	c8->SetGrid();
	TH1F *punto4 = new TH1F("h4","punto 4",10000,2300000,2428509);
	for(int i = 0; i < 5000000; i++){
		int b = 0;
		for(int j = 0; j < 101; j++){
			int c = gRandom->Uniform(2428509);//se queda con la mas alta
			if (c > b)b = c;
		}
		//cout<<b<<endl;
		punto4->Fill(b);
	}	

	int norm4 = punto4->GetEntries();
	punto4->Scale(1./norm4*10000/128509.);
	
	TGraph *teo4 = new TGraph();
	for(int i = 2300000; i < 2428509; i++){
		double puntito = 101;
		for (int j = 0; j < 101-1;j++){//si se desarrolla la ecuacion de la consigna se tiene un cociente de productorias de k terminos, si calculo cada uno por separado la maquina no da abasto pero si voy mulitplicado y dividiendo de a uno puede
			puntito = puntito*(i-1-j)*1./(2428509-j);
			//cout<<point<<endl;
		}
		puntito = puntito*1./(2428509-101+1);
		teo4->SetPoint(i-2300000,i,puntito);
	}

	TGraph *vacio = new TGraph();
	vacio->SetPoint(0,MyList[100],0);//este truquito es porque si dibujo primero el histograma me aparece un cuadro con Nentries que no quiero pero si dibujo primero la teorica no se ve porque queda abajo
	vacio->SetPoint(1,2428509,45e-6);
	vacio->SetPoint(2,2300000,0);
	vacio->SetLineColor(255);//invisible
	vacio->Draw();
	punto4->Draw("HISTsame");
	teo4->Draw("SAME");

	vacio->SetTitle("Densidad de probabilidad de la maxima patente dada la maxima patente en circulacion y el numero observado");
	vacio->GetXaxis()->SetTitle("Maxima patente observada");
	vacio->GetYaxis()->SetTitle("Densidad de probabilidad");
	vacio->GetXaxis()->CenterTitle();
	vacio->GetYaxis()->CenterTitle();
	TLegend *leg4 = new TLegend(0.1561605,0.5796178,0.5329513,0.85138);
	leg4->AddEntry(teo4,"Distribucion teorica","l");
	leg4->AddEntry(punto4,"Distribucion hallada computacionalmente","l");
	leg4->Draw("SAME");
	c8->SaveAs("imagen4.png");

	//----Punto 4b----
	TCanvas *c9 = new TCanvas("c9","punto 4b",200,10,700,500);
	c9->SetGrid();
	double proba4 = 0;
	double dist4[128509];

	TGraph *punto4b = new TGraph();
	for(int i = MyList[100]; i < MyList[100] + 128509; i++){
		double punto = 101;
		for (int j = 0; j < 101-1;j++){
			punto = punto*(MyList[100]-1-j)*1./(i-j);
			//cout<<point<<endl;
		}
		punto = punto*1./(i-101+1);
		proba4 = proba4 + punto;
		dist4[i-MyList[100]] = punto;
	}

	punto4b->SetPoint(0,MyList[100],0);
	for(int i = 0; i < 128509; i++){
		punto4b->SetPoint(i+1,i+MyList[100],dist4[i]*1./proba4);
	}
	punto4b->Draw();

	double esp4;
	for(int i = 0; i < 128509; i++){
		esp4 = esp4+dist4[i]*(i+MyList[100]);
	}
	cout<<"La esperanza para n es "<<esp4<<endl;

	TGraph *m4 = new TGraph();
	for(int i = 0; i < 15; i++){
		m4->SetPoint(i,2428509,i/14.*dist4[2428509-MyList[100]]);
	}
	m4->SetLineColor(62);
	m4->Draw("SAME");

	double pvalor4;//el nombre pvalor no es 100% correcto porque no estoy haciendo ningun test pero al fin y al cabo es la chance de lo mismo o peor
	for(int i = 2428509-MyList[100]; i < 128509; i++){
		pvalor4 = pvalor4 + dist4[i];
	}
	
	cout<<"La probabilidad de tener un peor estimador de la patente mas alta es "<<pvalor4<<endl;

	punto4b->SetTitle("Densidad de probabilidad para la maxima patente emitida dada la maxima patente observada");
	punto4b->GetXaxis()->SetTitle("Maxima patente emitida");
	punto4b->GetYaxis()->SetTitle("Densidad de probabilidad");
	punto4b->GetXaxis()->CenterTitle();
	punto4b->GetYaxis()->CenterTitle();
	TLegend *leg5 = new TLegend(.4,.6,.8,.8);
	leg5->AddEntry(punto4b,"Distribucion teorica obtenida por Bayes","l");
	leg5->AddEntry(m4,"Mayor patente emitida al dia de la medicion","l");
	leg5->Draw("SAME");
	c9->SaveAs("imagen5.png");
	//-----------------------------------------------------------Punto 5----------------------------------------------
	//Lista alternativa de patentes recolectada por Josefina Catoni, en las localidades Vicente Lopez y Olivos del partido de Vicente Lopez
	int HerList[177] = {4725,14444,125855,127902,142231,163711,171840,175572,200242,209988,224139,234344,273798,312188,312579,324269,330777,363500,370775,382854,383563,390285,399461,403517,411340,421992,424389,426913,426917,428657,445103,460458,460462,469713,483300,483492,491809,516764,523396,535078,556703,570855,581273,585010,587962,610711,616706,616855,655317,655974,659001,694198,702728,718093,733231,738020,747841,766851,787212,795383,802092,838687,842403,889193,921603,975655,981160,988009,1002128,1005927,1012533,1050143,1082051,1125401,1125408,1137154,1140363,1153624,1163904,1238228,1257330,1267698,1278364,1303818,1328896,1349470,1376755,1383977,1389923,1404174,1425832,1438995,1456406,1463619,1471359,1477498,1487835,1491301,1491306,1491499,1495834,1495923,1500365,1503372,1537489,1570404,1583374,1613398,1624903,1630674,1646383,1649944,1671987,1687845,1690158,1694904,1695574,1726876,1726879,1747085,1753863,1774742,1783909,1787541,1797109,1797114,1820564,1831461,1834572,1841597,1842992,1858635,1871189,1872015,1875295,1879628,1889028,1920917,1933492,1957736,1976881,1999638,2022308,2022806,2034091,2036751,2040607,2043846,2047771,2048038,2082736,2092940,2100598,2100773,2112668,2137395,2144646,2161872,2164129,2174593,2177955,2182631,2190333,2219865,2249597,2251622,2270393,2280008,2284789,2290641,2302137,2304209,2306516,2307796,2335276,2341198,2365091};
	int OurList[177+101];
	int indices[177+101];
	int MyCounter = 0;
	int HerCounter = 0;
	for(int i = 0; i < 177+101; i++){//ordena la lista de los dos juntos
		if (MyCounter < 101){//el vector indices es 1 cuando en esa posicion en OurList el elemento es de MyList
			if (HerCounter < 177){
				if (MyList[MyCounter]<HerList[HerCounter]){
					OurList[i] = MyList[MyCounter];
					MyCounter++;
					indices[i] = 1;
				}
				else if (MyList[MyCounter]>HerList[HerCounter]){
					OurList[i] = HerList[HerCounter];
					HerCounter++;
				}
			}
			else{//por si llega al final en la mia
				OurList[i] = MyList[MyCounter];
				MyCounter++;
				indices[i] = 1;
			}
		}
		else{//por si llega al final en la de Jose
			OurList[i] = HerList[HerCounter];
			HerCounter++;
		}
	}
	int wilco = 0;
	for(int i = 0; i < 177+101; i++){
		if (indices[i] == 1)wilco = wilco + i +1;//el + 1 para que sume 1 en la primera en vez de 0 y asi siguiendo
		//cout<<OurList[i]<<" "<<indices[i]<<" "<<wilco<<endl;
	}
	double esp = 101./2*(101+177+1);
	double sigm = pow(101*177./12*(101+177+1),1./2);
	double pvalor5 = 1-2*G((wilco-esp)/sigm);

	TCanvas *c52 = new TCanvas("c52","punto 5 A",200,10,700,500);
	c52->SetGrid();
	TGraph *wilcoxon = new TGraph();
	for(int i = 0; i < 300; i++){//grafico de densidad de prob de wilcoxon aproximado por gaussiana
		double x = i/300.*(10*sigm)+esp-5*sigm;
		wilcoxon->SetPoint(i,x,pow(2*3.1415926*sigm*sigm,-0.5)*pow(2.71828,-0.5*pow((x-esp)*1./sigm,2)));
	}
	wilcoxon->Draw();

	TGraph *MyWIlco = new TGraph();
	for (int i = 0; i < 15; i++){	
		MyWIlco->SetPoint(i,wilco,i/14.*pow(2*3.1415926*sigm*sigm,-0.5)*pow(2.71828,-0.5*pow((wilco-esp)*1./sigm,2)));
	}
	MyWIlco->SetLineColor(64);
	MyWIlco->Draw("SAME");
	cout<<"el Wilco es "<<wilco<<" y su p-valor es "<<pvalor5<<" ("<<(wilco-esp)/sigm<<" sigmas)"<<endl;
	
	wilcoxon->SetTitle("Test de Wilcoxon");
	wilcoxon->GetXaxis()->SetTitle("Estadistico de Wilcoxon");
	wilcoxon->GetYaxis()->SetTitle("Densidad de probabilidad");
	wilcoxon->GetXaxis()->CenterTitle();
	wilcoxon->GetYaxis()->CenterTitle();
	TLegend *leg7 = new TLegend(0.5687679,0.6666667,0.8911175,0.8832272);
	leg7->AddEntry(wilcoxon,"Dist del est de wilcoxon aproximada por normal","l");
	leg7->AddEntry(MyWIlco,"valor obtenido para el estadistico de wilcoxon","l");
	leg7->Draw("SAME");
	c52->SaveAs("imagen7.png");

	//-----ploteo de las dos cumulativas, analogo al que hay al principio para una sola
	TCanvas *punto5 = new TCanvas("c4","punto 5",200,10,700,500);
	punto5->SetGrid();
	double Jose[301];
	Jose[0] = 0;
	for(int i = 1; i < 300; i++){
		for (int j = 0; j < 177; j++){
				if(i*2428509./300 >= HerList[j-1]){
					if(i*2428509./300 < HerList[j])Jose[i] = j/177.;
				}
			}
	}
	for(int i = 293; i < 301; i++)Jose[i] = 1;

	TGraph *Catoni = new TGraph();
	for (int i = 0; i < 300; i++){
		Catoni->SetPoint(i,i*2428509./300,Jose[i]);
	}
	Catoni->SetPoint(300,2428509,1);
	Catoni->SetLineColor(45);
	Catoni->Draw();
	emp->Draw("same");
	
	Catoni->SetTitle("Comparacion entre dos distribuciones cumulativas experimentales adquiridas en distintos lugares");
	Catoni->GetXaxis()->SetTitle("Patente");
	Catoni->GetYaxis()->SetTitle("Probabilidad cumulativa");
	Catoni->GetXaxis()->CenterTitle();
	Catoni->GetYaxis()->CenterTitle();
	TLegend *leg6 = new TLegend(0.1404011,0.6921444,0.5916905,0.8492569);
	leg6->AddEntry(Catoni,"Distribucion cumulativa de la zona Vicente Lopez-Olivos","l");
	leg6->AddEntry(emp,"Distribucion cumulativa de la zona Versalles-Liniers","l");
	leg6->Draw("SAME");
	punto5->SaveAs("imagen6.png");
	//-----------------------------------Punto 5b---------------------------------
	int bx[101];//vectores que van a ser valores aleatorios
	int by[177];//de distribucion uniforme
	double promx;
	double promy;
	double Sx2;
	double Sy2;
	double UMC;//UMonteCarlo
	int Nbins5 = 200;
	TH1F *distU = new TH1F("h2","distribucion del estadistico U",Nbins5,-6,6);
	for(int j = 0; j < 500000; j++){
		promx = 0;
		promy = 0;
		Sx2 = 0;
		Sy2 = 0;
		for(int i = 0; i < 101; i++)bx[i] = gRandom->Uniform(2428509);
		for(int i = 0; i < 177; i++)by[i] = gRandom->Uniform(2428509);
		for(int i = 0; i < 101; i++)promx = promx+bx[i];
		for(int i = 0; i < 177; i++)promy = promy+by[i];
		promx = promx/101.;
		promy = promy/177.;
		for(int i = 0; i < 101; i++)Sx2 = Sx2 + pow(bx[i]-promx,2);
		for(int i = 0; i < 177; i++)Sy2 = Sy2 + pow(by[i]-promy,2);
		UMC = (promx-promy)*pow((101+177-2)/((1/101.+1/177.)*(Sx2 + Sy2)),0.5);
		distU->Fill(UMC);
	}

	TCanvas *c5 = new TCanvas("c5","distribucion de U",200,10,700,500);
	c5->SetGrid();
	double norm5 = distU->GetEntries();
	//cout<<norm5<<endl;
	distU->Scale(1./norm5*Nbins5/12.);
	//no ploteo aca porque todavia no calcule cuanto me dio el U

	//-----------------------------------Punto 5c---------------------------------
	double MyPromedio = 0.;
	for(int i = 0; i < 101; i++){
		MyPromedio = MyPromedio + MyList[i];
	}
	MyPromedio = MyPromedio/101.;

	double HerPromedio = 0;
	for(int i = 0; i < 177; i++){
		HerPromedio = HerPromedio + HerList[i];
	}
	HerPromedio = HerPromedio/177.;

	double MyS;
	for(int i = 0; i < 101; i++){
		MyS = MyS + pow(MyList[i]-MyPromedio,2);
	}

	double HerS;
	for(int i = 0; i < 177; i++){
		HerS = HerS + pow(HerList[i]-HerPromedio,2);
	}

	double Umedido = (MyPromedio-HerPromedio)*pow((101+177-2)/((1/101.+1/177.)*(MyS + HerS)),0.5);
	//cout<<Umedido<<endl;
	double pvalor5b = 0;
	for(int i = 0; i < Nbins5; i++){
		if ((-6+12.*i*1./Nbins5)>Umedido){
			pvalor5b = pvalor5b + distU->GetBinContent(i);
			//cout<<distU->GetBinContent(i)<<" "<<pvalor5b<<endl;
		}
	}
	TGraph *Ugraf = new TGraph();
	double auxU = (Umedido+6)/12.*Nbins5;
	int binU = auxU;
	//cout<<binU<<"  "<<distU->GetBinContent(binU)<<endl;
	for(int i = 0; i < 15; i++){
		Ugraf->SetPoint(i,12.*binU/Nbins5-6,i/14*distU->GetBinContent(binU));
	}

	vacio->SetPoint(0,-6,0.4);
	vacio->SetPoint(1,6,0);
	vacio->SetPoint(2,5.8,0.1);
	vacio->Draw();
	Ugraf->Draw("SAME");
	distU->Draw("HISTsame");
	pvalor5b = pvalor5b*1./Nbins5*12.;
	pvalor5b = 2*pvalor5b;

	cout<<"el U dio "<<Umedido<<" y su p-valor es "<<pvalor5b<<endl;

	vacio->SetTitle("Test usando el estadistico U");
	vacio->GetXaxis()->SetTitle("Estadistico U");
	vacio->GetYaxis()->SetTitle("Densidad de probabilidad");
	vacio->GetXaxis()->CenterTitle();
	vacio->GetYaxis()->CenterTitle();
	TLegend *leg8 = new TLegend(0.5644699,0.6624204,0.8911175,0.8832272);
	leg8->AddEntry(distU,"Densidad de probabilidad del estadistico U hallada computacionalmente","l");
	leg8->AddEntry(Ugraf,"Valor obtenido para el estadistico U");
	leg8->Draw("SAME");
	c5->SaveAs("imagen8.png");
	//-------------------------------------------------------Punto 6----------------------------
	int Nbins6 = 400;
	TH1F *punto6 = new TH1F("h3","distribucion del test combinado",Nbins6,0,20);
	for(int i = 0; i < 1000000; i++){
		double pwr = gRandom->Uniform(1);
		double ptr = gRandom->Uniform(1);
		double T = -2*(log(pwr)+log(ptr));
		punto6->Fill(T);
	}

	TCanvas *c6 = new TCanvas("c6","punto 6",200,10,700,500);
	c6->SetGrid();

	int norm6 = punto6->GetEntries();
	punto6->Scale(1./norm6*Nbins6/20.);

	TGraph *chi2 = new TGraph();
	for(int i = 0; i < 300; i++){
		double x6 = i/300.*20;
		chi2->SetPoint(i,x6,1./4*x6*pow(2.71828,-x6/2.));
	}
	chi2->SetLineColor(45);

	vacio->SetPoint(0,0,0.18);
	vacio->SetPoint(1,20,0);
	vacio->SetPoint(2,1,0.1);
	vacio->Draw();
	punto6->Draw("HISTsame");
	chi2->Draw("SAME");
	
	double p6m = -2*log(pvalor5*pvalor5b);
	int bin6 = Nbins6*p6m/20.; 
	TGraph *p6 = new TGraph();
	for(int i = 0; i < 15; i++){
		p6->SetPoint(i,bin6/400.*20,i/14*punto6->GetBinContent(bin6));
	}
	p6->Draw("SAME");

	double integral6 = 0;
	for(int i = 0; i < bin6; i++){
		integral6 = integral6 + punto6->GetBinContent(i);
	}
	integral6 = integral6*20./400.;
	double pvalor6 = 1-integral6;
	cout<<"el T dio "<<p6m<<" y su p-valor es "<<pvalor6<<endl;

	vacio->SetTitle("Combinacion de tests Wilcoxon y U");
	vacio->GetXaxis()->SetTitle("Estadistico T");
	vacio->GetYaxis()->SetTitle("Densidad de probabilidad");
	vacio->GetXaxis()->CenterTitle();
	vacio->GetYaxis()->CenterTitle();
	TLegend *leg9 = new TLegend(0.3223496,0.6072187,0.8492837,0.8450106);
	leg9->AddEntry(chi2,"Distribucion teorica chi cuadrado de 4 grados de libertad","l");
	leg9->AddEntry(punto6,"Distribucion del estadistico T hallada computacionalmente","l");
	leg9->AddEntry(p6,"Valor obtenido para el estadistico T","l");
	leg9->Draw("SAME");
	c6->SaveAs("imagen9.png");
	//---------------------------------------------------Punto 7-------------------------------
	int m7 = MyList[100];
	int n7 = 2428509;
	int k7 = 101;

	TGraph *punto7 = new TGraph();
	int istart = 2300000;
	double proba7;
	double dist7[n7-istart];
	for(int i = istart; i < n7; i++){
		double point = k7;
		for (int j = 0; j < k7-1;j++){
			point = point*(i-1-j)*1./(n7-j);
			//cout<<point<<endl;
		}
		point = point*1./(n7-k7+1);
		proba7 = proba7 + point;
		dist7[i-istart] = point;
		punto7->SetPoint(i-istart,i,point);
	}

	punto7->SetPoint(n7-istart,n7,0);
	//cout<<proba7<<endl;
	TCanvas *c7 = new TCanvas("c7","punto 7",200,10,700,500);
	c7->SetGrid();
	punto7->Draw();
	//cout<<dist7[m7-istart]<<endl;
	TGraph *medido7 = new TGraph();
	for(int i = 0; i < 15; i++){
		medido7->SetPoint(i,m7,dist7[m7-istart]*i/14.);
	}
	medido7->SetLineColor(45);
	medido7->Draw("SAME");

	double pderecha;
	for(int i = m7; i < n7; i++)pderecha = pderecha + dist7[i-istart];
	double pvalor7 = 1-pderecha;

	cout<<"el p-valor de haber mentido es "<<pvalor7<<endl;

	punto7->SetTitle("Test con la maxima patente hallada");
	punto7->GetXaxis()->SetTitle("Maxima patente observada");
	punto7->GetYaxis()->SetTitle("Densidad de probabilidad");
	punto7->GetXaxis()->CenterTitle();
	punto7->GetYaxis()->CenterTitle();
	TLegend *legx = new TLegend(0.1676218,0.5774947,0.6401146,0.8046709);
	legx->AddEntry(punto7,"Densidad de probabilidad para la maxima patente hallada","l");
	legx->AddEntry(medido7,"Maxima patente hallada");
	legx->Draw("SAME");
	c7->SaveAs("imagenx.png");
}