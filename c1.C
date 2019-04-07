void c1()
{
//=========Macro generated from canvas: c1/Data
//=========  (Wed Mar 13 00:44:15 2019) by ROOT version 6.14/02
   TCanvas *c1 = new TCanvas("c1", "Data",208,41,700,500);
   c1->Range(1.75,2.0275,3.25,4.7425);
   c1->SetFillColor(27);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetGridx();
   c1->SetGridy();
   c1->SetFrameFillColor(0);
   c1->SetFrameBorderMode(0);
   c1->SetFrameBorderMode(0);
   
   Double_t Graph0_fx1001[11] = {
   2,
   2.1,
   2.2,
   2.3,
   2.4,
   2.5,
   2.6,
   2.7,
   2.8,
   2.9,
   3};
   Double_t Graph0_fy1001[11] = {
   2.78,
   3.29,
   3.29,
   3.33,
   3.23,
   3.69,
   3.46,
   3.87,
   3.62,
   3.4,
   3.99};
   Double_t Graph0_fex1001[11] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph0_fey1001[11] = {
   0.3,
   0.3,
   0.3,
   0.3,
   0.3,
   0.3,
   0.3,
   0.3,
   0.3,
   0.3,
   0.3};
   TGraphErrors *gre = new TGraphErrors(11,Graph0_fx1001,Graph0_fy1001,Graph0_fex1001,Graph0_fey1001);
   gre->SetName("Graph0");
   gre->SetTitle("datos con su ajuste");
   gre->SetFillStyle(1000);
   gre->SetMarkerColor(4);
   gre->SetMarkerStyle(21);
   
   TH1F *Graph_Graph01001 = new TH1F("Graph_Graph01001","datos con su ajuste",100,1.9,3.1);
   Graph_Graph01001->SetMinimum(2.299);
   Graph_Graph01001->SetMaximum(4.471);
   Graph_Graph01001->SetDirectory(0);
   Graph_Graph01001->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   Graph_Graph01001->SetLineColor(ci);
   Graph_Graph01001->GetXaxis()->SetLabelFont(42);
   Graph_Graph01001->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph01001->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph01001->GetXaxis()->SetTitleFont(42);
   Graph_Graph01001->GetYaxis()->SetLabelFont(42);
   Graph_Graph01001->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph01001->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph01001->GetYaxis()->SetTitleOffset(0);
   Graph_Graph01001->GetYaxis()->SetTitleFont(42);
   Graph_Graph01001->GetZaxis()->SetLabelFont(42);
   Graph_Graph01001->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph01001->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph01001->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph01001);
   
   gre->Draw("ap");
   
   TPaveLabel *pl = new TPaveLabel(-2.722343,6.44797,1.572668,6.937022,"New Title","br");
   pl->SetTextSize(0.99);
   pl->Draw();
   
   Double_t Graph1_fx1002[11] = {
   2,
   2.1,
   2.2,
   2.3,
   2.4,
   2.5,
   2.6,
   2.7,
   2.8,
   2.9,
   3};
   Double_t Graph1_fy1002[11] = {
   3.050455,
   3.130364,
   3.210273,
   3.290182,
   3.370091,
   3.45,
   3.529909,
   3.609818,
   3.689727,
   3.769636,
   3.849545};
   Double_t Graph1_fex1002[11] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph1_fey1002[11] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   gre = new TGraphErrors(11,Graph1_fx1002,Graph1_fy1002,Graph1_fex1002,Graph1_fey1002);
   gre->SetName("Graph1");
   gre->SetTitle("ajuste");
   gre->SetFillStyle(1000);
   gre->SetLineColor(82);
   
   TH1F *Graph_Graph11002 = new TH1F("Graph_Graph11002","ajuste",100,1.9,3.1);
   Graph_Graph11002->SetMinimum(2.970545);
   Graph_Graph11002->SetMaximum(3.929455);
   Graph_Graph11002->SetDirectory(0);
   Graph_Graph11002->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph11002->SetLineColor(ci);
   Graph_Graph11002->GetXaxis()->SetLabelFont(42);
   Graph_Graph11002->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph11002->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph11002->GetXaxis()->SetTitleFont(42);
   Graph_Graph11002->GetYaxis()->SetLabelFont(42);
   Graph_Graph11002->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph11002->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph11002->GetYaxis()->SetTitleOffset(0);
   Graph_Graph11002->GetYaxis()->SetTitleFont(42);
   Graph_Graph11002->GetZaxis()->SetLabelFont(42);
   Graph_Graph11002->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph11002->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph11002->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph11002);
   
   gre->Draw("");
   
   TLegend *leg = new TLegend(0.1131805,0.6561181,0.4140401,0.8670886,NULL,"brNDC");
   leg->SetBorderSize(1);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("Graph0","datos","lpf");
   entry->SetFillStyle(1000);
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(4);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("Graph1","ajuste","lpflpf");
   entry->SetFillStyle(1000);
   entry->SetLineColor(82);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(1);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   leg->Draw();
   
   TPaveText *pt = new TPaveText(0.3295415,0.9342405,0.6704585,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *pt_LaTex = pt->AddText("datos con su ajuste");
   pt->Draw();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
