Int_t color[]={kRed,kMagenta+1,kViolet-3,kOrange+1,kYellow+1,kGreen+1,kCyan,kBlue,kGray+2};


void ana_MC(){
  gSystem->Load("libMinuit.so");
  gSystem->Load("libANALYSIS");
  gSystem->Load("libANALYSISalice");
  gSystem->Load("libCORRFW");
  gSystem->Load("libPWGTools");
  gSystem->Load("libPWGCFCorrelationsBase");

  TFile*file0 =new TFile("AnalysisResult_23012018_2.root");
  if(!file0){
    cout<<"no rootfile"<<endl;
    return;
  }
  
  TList* list = (TList*) file0->Get("QA_1");
  gStyle->SetOptStat(0);       
  const Int_t ncanvas=7;
  TCanvas*ch[ncanvas];
  for(Int_t i=0;i<ncanvas;i++){
    ch[i]=new TCanvas(Form("canvasmc_%d",i),Form("canvas_%d",i),600,400);
  }

  TH2F*fdNdetaOrigin=(TH2F*)list->FindObject("dNdetaOrigin");
  TH2F*fdNdetaOriginMulthit=(TH2F*)list->FindObject("dNdetaOriginMulthit");
  ch[0]->cd();
  fdNdetaOrigin->Draw("COLZ");
  
  THStack *hs = new THStack("hs","test stacked histograms");
  TH1D* hetaorigin[8];
  TH1D* hetaoriginmulthit[8];
  TH1D* hetasum;
  TH1D* hetasummulthit;
  for(Int_t i=0;i<8;i++){
    hetaorigin[i]=(TH1D*)fdNdetaOrigin->ProjectionX(Form("fetaorigin_%d",i),i+1,i+1);
    hetaoriginmulthit[i]=(TH1D*)fdNdetaOriginMulthit->ProjectionX(Form("fetaoriginmulthit_%d",i),i+1,i+1);
    if(i>0){
      hetaoriginmulthit[i]->SetFillColor(color[i]);
      if(i==1) hetasum=(TH1D*)hetaoriginmulthit[1]->Clone("hetasum");
      else hetasum->Add(hetaoriginmulthit[i]);
      hs->Add(hetaoriginmulthit[i]);
    }
  }
  ch[1]->cd();
  hetaorigin[0]->Draw();
  hetaorigin[0]->SetLineColor(2); 
  hetaorigin[0]->SetLineWidth(2);
  SetHistoStyle1D(hetaorigin[0],"","","");
  ch[2]->cd();
  hs->Draw();
  TLegend*leg1=new TLegend(0.55,0.2,0.8,0.45,"","NDC");
  leg1->SetTextSize(0.04);
  leg1->SetFillColor(0);
  leg1->SetBorderSize(0);
  leg1->AddEntry(hetaoriginmulthit[1],"Primary");
  leg1->AddEntry(hetaoriginmulthit[2],"Eary decay");
  leg1->AddEntry(hetaoriginmulthit[3],"Beam Pipe");
  leg1->AddEntry(hetaoriginmulthit[4],"ITS and support");
  leg1->AddEntry(hetaoriginmulthit[5],"FMD and support");
  leg1->AddEntry(hetaoriginmulthit[6],"Other");
  leg1->AddEntry(hetaoriginmulthit[7],"Eary decay");
  leg1->Draw("SAME");
  
  ch[3]->cd();
  TH1F*clone_heta=(TH1F*)hetasum->Clone("clone_heta");
  clone_heta->Draw();
  ch[4]->cd();
  hetasum->Divide(hetaorigin[0]);
  hetasum->Draw();
  SetHistoStyle1D(hetasum,"#eta","FMD response/Primary","");
  
  ch[5]->cd();
  TH2D*fh2_FMD_eta_phi_prim=(TH2D*)list->FindObject("fh2_FMD_eta_phi_prim");
  fh2_FMD_eta_phi_prim->Draw("COLZ");
  ch[6]->cd();
  TH1D*pro_fh2prim=(TH1D*)fh2_FMD_eta_phi_prim->ProjectionX("pro_fh2prim");
  pro_fh2prim->Draw();
  
  return;
  
  AliTHn*fhistfmd=(AliTHn*)(list->FindObject("fhistmcprim"));
  fhistfmd->FillParent();
  fhistfmd->DeleteContainers();
  ch[0]->cd();
  fhistfmd->ShowProjection(0,0)->Draw();
  
  
  // ana_primetaphi("~/work/local_alicework/MCESDanalysis/AnalysisResults.root","primary",kFALSE);



  //  ana_primetaphi("../result/AnalysisResults_DPMJET_LHC17f2b_19122017.root","20171219",kTRUE);
}
void ana_primetaphi(char* name,char*outname,Bool_t savefig){
  TFile*file0 =new TFile(name);
  TList* list = (TList*) file0->Get("QA_1");
  gStyle->SetOptStat(0);       
  const Int_t ncanvas=2;
  TCanvas*ch[ncanvas];
  for(Int_t i=0;i<ncanvas;i++){
    ch[i]=new TCanvas(Form("canvasmc_%d",i),Form("canvas_%d",i),600,400);
  }
  AliTHn*fhistmcprim=(AliTHn*)(list->FindObject("fhistmcprim"));
  fhistmcprim->FillParent();
  fhistmcprim->DeleteContainers();
  
  const ncentbin=7;
  Double_t  centbin[ncentbin]={0,5,10,20,40,60,100};
  
  ch[0]->cd();
  TH1D*centeta[ncentbin-1];
  for(Int_t icent=0;icent<ncentbin-1;icent++){
    fhistmcprim->SetRangeUser(3,centbin[icent]+0.001,centbin[icent+1]-0.001);
    centeta[icent]=(TH1D*)fhistmcprim->ShowProjection(1,0);
    centeta[icent]->SetLineColor(color[icent]);
    centeta[icent]->Draw("SAME");
  }                     
  fhistmcprim->SetRangeUser(3,0,100);
  ch[1]->cd();
  const nvzbin=10;
  Double_t vzbin[nvzbin+1]={-10.,-8.,-6.,-4.,-2.,0.,2.,4.,6.,8.,10.};
  TH2D*vzetaphi[nvzbin];
  TH1D*vzeta[nvzbin];
  for(Int_t i=0;i<nvzbin;i++){
    fhistmcprim->SetRangeUser(4,vzbin[i]+0.0001,vzbin[i+1]-0.001);
    vzetaphi[i]=(TH2D*)fhistmcprim->ShowProjection(1,2,0);
    vzeta[i]=(TH1D*)fhistmcprim->ShowProjection(1,0);
    vzeta[i]->SetLineColor(color[i]);
    vzeta[i]->Draw("SAME");
  }
  


}


void ana_prim1d(char* name,char*outname,Bool_t savefig){
  TFile*file0 =new TFile(name);
  TList* list = (TList*) file0->Get("QA_1");
  gStyle->SetOptStat(0);       
  const Int_t ncanvas=5;
  TCanvas*ch[ncanvas];
  for(Int_t i=0;i<ncanvas;i++){
    ch[i]=new TCanvas(Form("canvasmc_%d",i),Form("canvas_%d",i),600,400);
  }
 AliTHn*fhistmcprim=(AliTHn*)(list->FindObject("fhistmcprim"));
 fhistmcprim->FillParent();
 fhistmcprim->DeleteContainers();
 ch[0]->cd();
 TH1D*ptprim=(TH1D*)fhistmcprim->ShowProjection(0,0);
 ptprim->Draw();
 ch[1]->cd();
 TH1D*etaprim=(TH1D*)fhistmcprim->ShowProjection(1,0);
 etaprim->Draw(); 
 ch[2]->cd();
 TH1D*phiprim=(TH1D*)fhistmcprim->ShowProjection(2,0);
 phiprim->Draw();
 ch[3]->cd();
 TH1D*centprim=(TH1D*)fhistmcprim->ShowProjection(3,0);
 centprim->Draw();
 ch[4]->cd();
 TH1D*vzprim=(TH1D*)fhistmcprim->ShowProjection(4,0);
 vzprim->Draw();
 
 
}
void ana_all(char* name,char*outname,Bool_t savefig){
  TFile*file0 =new TFile(name);
  TList* list = (TList*) file0->Get("QA_1");
  gStyle->SetOptStat(0);       
  const Int_t ncanvas=2;
  TCanvas*ch[ncanvas];
  for(Int_t i=0;i<ncanvas;i++){
    ch[i]=new TCanvas(Form("histcanvas_%d",i),Form("canvas_%d",i),600,400);
  }
  /*
  ch[0]->cd();
  TH2D*fh2_FMD_acceptance=drawhist(list,"fh2_FMD_acceptance");
  SetHistoStyle2D(fh2_FMD_acceptance,"#eta","v_{z}","");
  fh2_FMD_acceptance->Draw("COLZ");
  ch[1]->cd();
  TH2D*fh2_FMD_eta_phi=drawhist(list,"fh2_FMD_eta_phi");
  SetHistoStyle2D(fh2_FMD_eta_phi,"#eta","#phi","");
  fh2_FMD_eta_phi->Draw("COLZ");
  ch[1]->SaveAs(Form("FMDetaphi_%s.pdf",outname));
  */
}
TH2D* drawhist(TList*list,char*name){
  if(!list) return;
  TH2D* hh=(TH2D*)(list->FindObject(name));
  return hh;
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
