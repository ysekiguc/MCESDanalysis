Int_t color[]={kRed,kMagenta+1,kViolet-3,kOrange+1,kYellow+1,kGreen+1,kCyan,kBlue,kGray+2};

void ana_FMDQA(){
  ana_all("../result/AnalysisResults_DPMJET_LHC17f2b_19122017.root","20171219",kTRUE);
  //  ana_comptandq();
}

void ana_all(char* name,char*outname,Bool_t savefig){
  //TFile*file0 =new TFile("../resutl_20170828/AnalysisResults_20170828_LHC16q_LHC16t.root");
  TFile*file0 =new TFile(name);
  TList* list = (TList*) file0->Get("QA_1");
  gStyle->SetOptStat(0);       
  const Int_t ncanvas=7;
  TCanvas*ch[ncanvas];
  for(Int_t i=0;i<ncanvas;i++){
    ch[i]=new TCanvas(Form("histcanvas_%d",i),Form("canvas_%d",i),600,400);
  }
  ch[0]->cd();
  TH2D*fhFMDV0=drawhist(list,"FMDV0");
  gPad->SetLogz();
  SetHistoStyle2D(fhFMDV0,"FMD1+FMD2+FMD3","V0A+V0C","");
  fhFMDV0->Draw("COLZ");
  
  ch[1]->cd();
  TH2D*fhFMDV0_post=drawhist(list,"FMDV0_post");
  gPad->SetLogz();
  SetHistoStyle2D(fhFMDV0_post,"FMD1+FMD2+FMD3","V0A+V0C","");
  fhFMDV0_post->Draw("COLZ");
  //  if(savefig)ch[1]->SaveAs(Form("FMDV0_post_%s.pdf",outname));
  
  ch[2]->cd();
  TH2D*fh2_FMD_acceptance=drawhist(list,"fh2_FMD_acceptance");
  SetHistoStyle2D(fh2_FMD_acceptance,"#eta","v_{z}","");
  fh2_FMD_acceptance->Draw("COLZ");
  ch[3]->cd();
  TH2D*fh2_FMD_eta_phi=drawhist(list,"fh2_FMD_eta_phi");
  SetHistoStyle2D(fh2_FMD_eta_phi,"#eta","#phi","");
  fh2_FMD_eta_phi->Draw("COLZ");
  ch[3]->SaveAs(Form("FMDetaphi_%s.pdf",outname));
  TH1D *fhproFMDeta = fh2_FMD_eta_phi->ProjectionX(Form("%s_proeta",fh2_FMD_eta_phi->GetName()));
  SetHistoStyle1D(fhproFMDeta,"#eta","Multiplicity","");
  fhproFMDeta->SetLineColor(color[0]);
  fhproFMDeta->SetLineWidth(2);
  ch[4]->cd();
  fhproFMDeta->Draw();
  ch[4]->SaveAs(Form("FMDetapro_%s.pdf",outname));
  ch[5]->cd();
  TH1D *fhproFMDphiAside = fh2_FMD_eta_phi->ProjectionY(Form("%s_prophia",fh2_FMD_eta_phi->GetName()),fh2_FMD_eta_phi->GetXaxis()->FindBin(0),200);
  fhproFMDphiAside->SetLineColor(color[0]);
  fhproFMDphiAside->SetLineWidth(2);
  fhproFMDphiAside->SetMinimum(0);
  SetHistoStyle1D(fhproFMDphiAside,"#phi","Multiplicity","");
  fhproFMDphiAside->Draw();
  TH1D *fhproFMDphiCside = fh2_FMD_eta_phi->ProjectionY(Form("%s_prophic",fh2_FMD_eta_phi->GetName()),1,fh2_FMD_eta_phi->GetXaxis()->FindBin(0.));
  fhproFMDphiCside->SetLineColor(color[1]);
  fhproFMDphiCside->SetLineWidth(2);
  fhproFMDphiCside->SetMinimum(0);
  SetHistoStyle1D(fhproFMDphiCside,"#phi","Multiplicity","");
  fhproFMDphiCside->Draw("SAME");
  TLegend*leg1=new TLegend(0.55,0.2,0.8,0.45,"","NDC");
  leg1->SetTextSize(0.04);
  leg1->SetFillColor(0);
  leg1->SetBorderSize(0);
  leg1->AddEntry(fhproFMDphiAside,"#eta>0");
  leg1->AddEntry(fhproFMDphiCside,"#eta<0");
  leg1->Draw("SAME");
  ch[5]->SaveAs(Form("FMDphipro_%s.pdf",outname));
  return;
}

void SetHistoStyle2D(TH2D*h, const char* xtitle, const char* ytitle, const char *title){
  gPad->SetLeftMargin(0.15);
  h->GetXaxis()->SetTitle(xtitle);
  h->GetYaxis()->SetTitle(ytitle);
   h->GetXaxis()->SetNdivisions(505);
  h->GetYaxis()->SetNdivisions(505);
  h->GetXaxis()->SetTitleSize(0.05);
  h->GetXaxis()->SetLabelSize(0.05);
  h->GetYaxis()->SetTitleSize(0.05);
  h->GetYaxis()->SetLabelSize(0.05);
  h->GetYaxis()->SetTitleOffset(1.1);
  h->GetXaxis()->SetTitleOffset(0.9);
  h->GetYaxis()->SetLabelOffset(0.01);
  h->SetTitle(title);

  //( (TGaxis*) h->GetYaxis())->SetMaxDigits(3);
}


void SetHistoStyle1D(TH1D*h, const char* xtitle, const char* ytitle, const char *title){
  //  gPad->SetLeftMargin(0.2);
  //gPad->SetRightMargin(0.01);
  //  gStyle->SetOptStat(0);
  //gStyle->SetPadLeftMargin(0.2);
  //gStyle->SetPadRightMargin(0.15);
  h->GetXaxis()->SetTitle(xtitle);
  h->GetYaxis()->SetTitle(ytitle);
  h->GetXaxis()->SetNdivisions(505);
  h->GetYaxis()->SetNdivisions(505);
  h->GetXaxis()->SetTitleSize(0.05);
  h->GetXaxis()->SetLabelSize(0.05);
  h->GetYaxis()->SetTitleSize(0.05);
  h->GetYaxis()->SetLabelSize(0.05);
  h->GetYaxis()->SetTitleOffset(1.);
  h->GetXaxis()->SetTitleOffset(0.9);
  h->GetYaxis()->SetLabelOffset(0.01);
  h->SetTitle(title);
  
    ( (TGaxis*) h->GetYaxis())->SetMaxDigits(3);
}
TH2D* drawhist(TList*list,char*name){
  if(!list) return;
  TH2D* hh=(TH2D*)(list->FindObject(name));
  return hh;
}


