Int_t color[]={kRed,kMagenta+1,kViolet-3,kOrange+1,kYellow+1,kGreen+1,kCyan,kBlue,kGray+2};

void ana_TPCQA(){
  AllQA();
  return;

}

void ana_comptandq(){
    
  gSystem->Load("libMinuit.so");
  gSystem->Load("libANALYSIS");
  gSystem->Load("libANALYSISalice");
  gSystem->Load("libCORRFW");
  gSystem->Load("libPWGTools");
  gSystem->Load("libPWGCFCorrelationsBase");

  Bool_t Fast=kTRUE;
  Bool_t wSDD=kTRUE;
  Bool_t woSDD=kTRUE;
  Bool_t IsLHC16q=kTRUE;
  Bool_t IsLHC16t=kTRUE;
  gStyle->SetOptStat(0);
  TList *list[6];
  TList *evelist[6];

  char* listname="Corr_BC";
  char* listname_event="pPbCorrelations_BC";
  
  if(Fast){
    TFile*file0 =new TFile("../resutl_20170828/AnalysisResults_1255_20170828_LHC16q_pass1_FAST.root");
    list[0] = (TList*) file0->Get(listname);
    evelist[0] = (TList*) file0->Get(listname_event);
  }

  if(wSDD){
    TFile*file1 =new TFile("../resutl_20170828/AnalysisResults_1254_20170828_LHC16q_pass1_CENT_wSDD.root");
    list[1] = (TList*) file1->Get(listname);
    evelist[1] = (TList*) file1->Get(listname_event);
  }

 if(woSDD){
   TFile*file2=new TFile("../resutl_20170828/AnalysisResults_1259_20170828_LHC16q_pass1_CENT_woSDD.root");
   list[2] = (TList*) file2->Get(listname);
   evelist[2] = (TList*) file2->Get(listname_event);
 }

 //LHC16t
 if(Fast){
   TFile*file3 =new TFile("../resutl_20170828/AnalysisResults_1258_20170828_LHC16t_pass1_FAST.root");
   list[3] = (TList*) file3->Get(listname);
   evelist[3] = (TList*) file3->Get(listname_event);
 }

  if(wSDD){
    TFile*file4 =new TFile("../resutl_20170828/AnalysisResults_1257_20170828_LHC16t_pass1_CENT_wSDD.root");
    list[4] = (TList*) file4->Get(listname);
    evelist[4] = (TList*) file4->Get(listname_event);
  }

 if(woSDD){
   TFile*file5=new TFile("../resutl_20170828/AnalysisResults_1256_20170828_LHC16t_pass1_CENT_woSDD.root");
   list[5] = (TList*) file5->Get(listname);
   evelist[5] = (TList*) file5->Get(listname_event);
 }

 Int_t nevents[6];
 TH1D* hstat[6];
 for(Int_t i=0;i<6;i++){
   hstat[i]=drawhist(evelist[i],"fHist_Stat");
   nevents[i]=hstat[i]->GetBinContent(7);
   //hstat[i]->Draw();
   //   cout<<nevents[i]<<endl;
 }
 // new TCanvas;
 const Int_t ncanvas=3;
 TCanvas*ch[ncanvas];
 for(Int_t i=0;i<ncanvas;i++){
   ch[i]=new TCanvas(Form("histcanvas_%d",i),Form("canvas_%d",i),600,400);
 }
 AliTHn* fHistLeadQA[6];
 for(Int_t i=0;i<6;i++){
   fHistLeadQA[i]=getalithn(list[i],"fHistLeadQA");
 }
 
 TH1D*hpt[6];
 for(Int_t i=0;i<6;i++){
   hpt[i]=drawhist(fHistLeadQA[i],"fHistLeadQA",0);
   hpt[i]->SetLineColor(color[i]);
   hpt[i]->SetLineWidth(2);
   hpt[i]->Sumw2();
   ch[0]->cd();
   hpt[i]->Scale(1./nevents[i]);
   SetHistoStyle1D(hpt[i],"p_{T}(GeV/c)","#frac{1}{dp_{T}N_{events}}","");
   gPad->SetLogy();
   hpt[i]->Draw("SAME");
 }
 
 TLegend*leg1=new TLegend(0.55,0.2,0.8,0.45,"","NDC");
 leg1->SetTextSize(0.04);
 leg1->SetFillColor(0);
 leg1->SetBorderSize(0);
 leg1->AddEntry(hpt[0],"LHC16q(FAST)");
 leg1->AddEntry(hpt[1],"LHC16q(wSDD)");
 leg1->AddEntry(hpt[2],"LHC16q(woSDD)");
 leg1->AddEntry(hpt[3],"LHC16t(Fast)");
 leg1->AddEntry(hpt[4],"LHC16t(wSDD)");
 leg1->AddEntry(hpt[5],"LHC16t(woSDD)");
 leg1->Draw("SAME");
 
 TH1D*heta[6];
 for(Int_t i=0;i<6;i++){
   heta[i]=drawhist(fHistLeadQA[i],"fHistLeadQA",1);
   heta[i]->SetLineColor(color[i]);
   heta[i]->SetLineWidth(2);
   heta[i]->Sumw2();
   ch[1]->cd();
   heta[i]->Scale(1./nevents[i]);
   SetHistoStyle1D(heta[i],"#eta","#frac{1}{N_{event}}","");
   heta[i]->Draw("SAME");
 }
 leg1->Draw("SAME");

 TH1D*hphi[6];
 for(Int_t i=0;i<6;i++){
   hphi[i]=drawhist(fHistLeadQA[i],"fHistLeadQA",2);
   hphi[i]->SetLineColor(color[i]);
   hphi[i]->SetLineWidth(2);
   hphi[i]->Sumw2();
   ch[2]->cd();
   hphi[i]->Scale(1./nevents[i]);
   SetHistoStyle1D(hphi[i],"#eta","#frac{1}{N_{event}}","");
   hphi[i]->GetYaxis()->SetRangeUser(0,2.7);
   hphi[i]->Draw("SAME");
 }
 leg1->Draw("SAME");
 
}
void AllQA(){
  char*figtag="28082017";
  gSystem->Load("libMinuit.so");
  gSystem->Load("libANALYSIS");
  gSystem->Load("libANALYSISalice");
  gSystem->Load("libCORRFW");
  gSystem->Load("libPWGTools");
  gSystem->Load("libPWGCFCorrelationsBase");
  char* listname="Corr_BC";
  char* listname_event="pPbCorrelations_BC";
  TFile*file0 =new TFile("../resutl_20170828/AnalysisResults_20170828_LHC16q_LHC16t.root");
  TList*  list = (TList*) file0->Get(listname);
  TList*  evelist = (TList*) file0->Get(listname_event);
  TH1D*hstat=(TH1D*)evelist->FindObject("fHist_Stat");
  TH1D*hcent=(TH1D*)evelist->FindObject("fHistCentrality");
  hstat->Draw();
  new TCanvas;
  hcent->Draw();
  const  Int_t ncent=6;//1-5,5-10,10-20,20-40,40-60,60-100
  TH1D*hpt[ncent];
  TH1D*heta[ncent];
  TH1D*hphi[ncent];
  Double_t cent[]={0,5,10,20,40,60,100};
  Float_t ncenteve[ncent];
  Float_t alleve=0;
  for(Int_t i=0;i<ncent;i++){
    ncenteve[i]=hcent->Integral(hcent->GetXaxis()->FindBin(cent[i]+0.001),hcent->GetXaxis()->FindBin(cent[i+1]-0.001));
    cout<<cent[i]+0.001<<" "<<cent[i+1]-0.001<<" "<<ncenteve[i]<<endl;
    alleve+=ncenteve[i];
  }
  cout<<"all number of events=="<<alleve<<endl;
  
  const Int_t ncanvas=4;
  TCanvas*ch[ncanvas];
  for(Int_t i=0;i<ncanvas;i++){
    ch[i]=new TCanvas(Form("histcanvas_%d",i),Form("canvas_%d",i),600,400);
  }
  const AliTHn* fHistLeadQA=getalithn(list,"fHistLeadQA");
  ch[0]->cd();
  gStyle->SetOptStat(0);
  for(Int_t i=0;i<ncent;i++){
    hpt[i] =drawhist(fHistLeadQA,cent[i],cent[i+1],0);
    hpt[i]->SetLineWidth(2);
    hpt[i]->Sumw2();
    hpt[i]->SetMarkerStyle(20);
    hpt[i]->SetMarkerSize(1);
    hpt[i]->SetMarkerColor(color[i]);
    hpt[i]->SetLineColor(color[i]);
    SetHistoStyle1D(hpt[i],"p_{T}(GeV/c)","#frac{dN}{N_{eve}dp_{T}}","");
    hpt[i]->Scale(1./ncenteve[i]);
    hpt[i]->GetXaxis()->SetRangeUser(0.3,4);
    hpt[i]->SetMinimum(0.01);
    gPad->SetLogy();
    hpt[i]->Draw("SAME");
  }
  TLegend*leg1=new TLegend(0.65,0.6,0.8,0.85,"","NDC");
  leg1->SetTextSize(0.04);
  leg1->SetFillColor(0);
  leg1->SetBorderSize(0);
  for(Int_t i=0;i<ncent;i++){
    leg1->AddEntry(hpt[i],Form("%d-%d %%",(Int_t)cent[i],(Int_t)cent[i+1]));
  }
  leg1->Draw("SAME");
  ch[0]->SaveAs(Form("ptQAsum_%s.pdf",figtag));
  ch[1]->cd();
  gStyle->SetOptStat(0);
  for(Int_t i=0;i<ncent;i++){
    heta[i] =drawhist(fHistLeadQA,cent[i],cent[i+1],1);
    heta[i]->Sumw2();
    
    heta[i]->SetLineWidth(2);
    
    heta[i]->SetMarkerStyle(20);
    heta[i]->SetMarkerSize(1);
    heta[i]->SetMarkerColor(color[i]);
    heta[i]->SetLineColor(color[i]);
    SetHistoStyle1D(heta[i],"#eta","#frac{dN}{N_{eve}d#eta}","");
    heta[i]->Scale(1./ncenteve[i]);
    //    heta[i]->GetYaxis()->SetRangeUser(0,35);
    gPad->SetRightMargin(0.2);
    heta[i]->Draw("SAME");
  }
  TLegend*leg2=new TLegend(0.82,0.4,1.,0.8,"","NDC");
  leg2->SetTextSize(0.04);
  leg2->SetFillColor(0);
  leg2->SetBorderSize(0);
  //  leg2->SetNColumns(2);
  for(Int_t i=0;i<ncent;i++){
    leg2->AddEntry(heta[i],Form("%d-%d %%",(Int_t)cent[i],(Int_t)cent[i+1]));
  }
  leg2->Draw("SAME");
  ch[1]->SaveAs(Form("etaQAsum_%s.pdf",figtag));

  ch[2]->cd();
  gStyle->SetOptStat(0);
  for(Int_t i=0;i<ncent;i++){
    hphi[i] =drawhist(fHistLeadQA,cent[i],cent[i+1],2);
    hphi[i]->SetLineWidth(2);
    hphi[i]->Sumw2();
    hphi[i]->SetMarkerStyle(20);
    hphi[i]->SetMarkerSize(1);
    hphi[i]->SetMarkerColor(color[i]);
    hphi[i]->SetLineColor(color[i]);
    SetHistoStyle1D(hphi[i],"#phi","#frac{dN}{N_{eve}d#phi}","");
    hphi[i]->Scale(1./ncenteve[i]);
    hphi[i]->SetMinimum(0);
    gPad->SetRightMargin(0.2);
    hphi[i]->Draw("SAME");
  }
  TLegend*leg3=new TLegend(0.82,0.4,1.,0.8,"","NDC");
  leg3->SetTextSize(0.04);
  leg3->SetFillColor(0);
  leg3->SetBorderSize(0);
  
  for(Int_t i=0;i<ncent;i++){
    leg3->AddEntry(hphi[i],Form("%d-%d %%",(Int_t)cent[i],(Int_t)cent[i+1]));
  }
  leg3->Draw("SAME");

  ch[2]->SaveAs(Form("phiQAsum_%s.pdf",figtag));

  ch[3]->cd();
  fHistLeadQA->SetRangeUser(3,0.001,99.999);
  fHistLeadQA->ShowProjection(1,2,0)->Draw("COLZ");
  

}

void SetHistoStyle1D(TH1D*h, const char* xtitle, const char* ytitle, const char *title){
    gPad->SetLeftMargin(0.15);
    //gPad->SetRightMargin(0.01);
  //  gStyle->SetOptStat(0);
  gStyle->SetPadLeftMargin(0.2);
  ////gStyle->SetPadRightMargin(0.15);
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
  
    ( (TGaxis*) h->GetYaxis())->SetMaxDigits(3);
}

TH1D* drawhist(TList*list,char*name){
  if(!list) return;
  TH1D* hh=(TH1D*)(list->FindObject(name));
  return hh;
}

AliTHn* getalithn(TList*list, char* name){
  AliTHn* h=(AliTHn*)(list->FindObject(name));
  h->FillParent();
  h->DeleteContainers();
  return h;
}

TH1D* drawhist(AliTHn*h,char*name,Int_t axis){
  TH1D*hh=h->ShowProjection(axis,0);
  for(Int_t i=0;i<hh->GetNbinsX();i++){
    Double_t width=hh->GetBinWidth(i+1);
    Double_t cont=hh->GetBinContent(i+1);
    hh->SetBinContent(i+1,cont/width);
  }
  return hh;
}

 TH1D* drawhist(const AliTHn*h,Double_t centmin,Double_t centmax,Int_t axis){
   h->SetRangeUser(3,centmin+0.001,centmax-0.001);
   TH1D*hh=h->ShowProjection(axis,0);
   for(Int_t i=0;i<hh->GetNbinsX();i++){
     Double_t width=hh->GetBinWidth(i+1);
     Double_t cont=hh->GetBinContent(i+1);
     hh->SetBinContent(i+1,cont/width);
   }
   return hh;
 }

void compglobal(TList*list, TList*list1,TList*list2,char*name){
  TH1D*h;
  TH1D*h1;
  TH1D*h2;

  if(list) {
    h=(TH1D*)(list->FindObject(name));
    SetHistoStyle1D(h,"","","");
      h->Draw();
    if(name=="fHist_Stat"){
     cout<<"number of analuzed event(Fast)"<<h->GetBinContent(6)<<endl;
    Int_t fnanaeve=h->GetBinContent(6);
    }else{
      Int_t nevent=h->Integral(0,h->GetNbinsX());
      Printf("%s,%d",name,nevent);
      h->Scale(1./nevent);
    }
    TH1D*h_clone=(TH1D*)h->Clone("h_clone");
  }
  
  if(list1) {
    h1=(TH1D*)(list1->FindObject(name));
    h1->SetLineColor(2);
    SetHistoStyle1D(h1,"","","");
    h1->Draw("SAME");
    if(name=="fHist_Stat") {
      cout<<"number of analuzed event(wSDD)"<<h1->GetBinContent(6)<<endl;
      Int_t fnanaeve1=h1->GetBinContent(6);
    }else{
      Int_t nevent1=h1->Integral(0,h1->GetNbinsX());
    Printf("%s,%d",name,nevent1);
    h1->Scale(1./nevent1);
    }
    TH1D*h1_clone=(TH1D*)h1->Clone("h1_clone");
  }

  if(list2){
    h2=(TH1D*)(list2->FindObject(name));
    if(name=="fHist_Stat") {
        cout<<"number of analuzed event(woSDD)"<<h2->GetBinContent(6)<<endl;
        Int_t fnanaeve2=h2->GetBinContent(6);
    }else {
      Int_t nevent2=h2->Integral(0,h2->GetNbinsX());
      Printf("%s,%d",name,nevent2);
      h2->Scale(1./nevent2);
    }
    h2->SetLineColor(6);
    SetHistoStyle1D(h2,"","","");
    h2->Draw("SAME");
    TH1D*h2_clone=(TH1D*)h2->Clone("h2_clone");
  }

  
  TLegend*leg=new TLegend(0.15,0.67,0.37,0.85,"","NDC");
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  if(h)  leg->AddEntry(h,"Fast");
  if(h1) leg->AddEntry(h1,"wSDD");
  if(h2) leg->AddEntry(h2,"woSDD");
  leg->Draw("SAME");
  /*
  if(list && list1 && list2){
    new TCanvas;
    //    h1_clone->Divide(h_clone);
    //h2_clone->Divide(h_clone);
    h1_clone->Draw();
    h2_clone->Draw("SAME");
  }
  */
  
}
