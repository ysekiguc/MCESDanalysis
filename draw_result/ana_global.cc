Int_t color[]={kRed,kMagenta+1,kViolet-3,kOrange+1,kYellow+1,kGreen+1,kCyan,kBlue,kGray+2};

void ana_global(){
  //  ana_all("../resutl_20170828/AnalysisResults_20170828_LHC16q_LHC16t.root","20170828",kTRUE);
  //  ana_comptandq();
  // ana_all("../result/AnalysisResults_DPMJET_LHC17f2b_19122017.root","20171219",kTRUE);
  ana_all("AnalysisResult_23012018_2.root","23012018",kTRUE);
}

void ana_all(char* name,char*outname,Bool_t savefig){
  TFile*file0 =new TFile(name);
  TList* list = (TList*) file0->Get("pPbCorrelations_1");
  gStyle->SetOptStat(0);       
  const Int_t ncanvas=3;
  TCanvas*ch[ncanvas];
  for(Int_t i=0;i<ncanvas;i++){
    ch[i]=new TCanvas(Form("histcanvas_%d",i),Form("canvas_%d",i),600,400);
  }
  ch[0]->cd();
  TH1D*hh2=drawhist(list,"fHist_Stat",kFALSE);
  hh2->SetLineColor(color[0]);
  //  hh2->SetMinimum(0);
  hh2->SetLineWidth(2);
  SetHistoStyle1D(hh2,"","Counts","");
  //  hh2->GetXaxis()->SetRangeUser(0,7);
  //  gPad->SetLogy();
  hh2->Draw();

  
  if(savefig) ch[0]->SaveAs(Form("eventstat_%s.pdf",outname));
  //Float_t neve=hh2->GetBinContent(7);

  ch[1]->cd();
  TH1D*hh1=drawhist(list,"fHistCentrality",kFALSE);
  hh1->SetLineColor(color[0]);
  hh1->SetMinimum(0);
  hh1->SetLineWidth(2);
  SetHistoStyle1D(hh1,"Centrality","Counts","");
  hh1->Draw();
  if(savefig) ch[1]->SaveAs(Form("centrality_%s.pdf",outname));

  ch[2]->cd();
  TH1D*hh=drawhist(list,"fHistzvertex",kFALSE);
  hh->SetLineColor(color[0]);
  hh->SetMinimum(0);
  hh->SetLineWidth(2);
  SetHistoStyle1D(hh,"v_{z}(cm)","Counts","");
  hh->Draw();
  if(savefig) ch[2]->SaveAs(Form("zvertex_%s.pdf",outname));

  return;
}
void ana_comptandq(){
  Bool_t Fast=kTRUE;
  Bool_t wSDD=kTRUE;
  Bool_t woSDD=kTRUE;
  Bool_t IsLHC16q=kTRUE;
  Bool_t IsLHC16t=kTRUE;
  gStyle->SetOptStat(0);
  TList *list[6];
  
  if(Fast){
    TFile*file0 =new TFile("../resutl_20170828/AnalysisResults_1255_20170828_LHC16q_pass1_FAST.root");
    list[0] = (TList*) file0->Get("pPbCorrelations_FC");
    TDirectoryFile* df=file0->Get("MultSelection");
    }

  if(wSDD){
    TFile*file1 =new TFile("../resutl_20170828/AnalysisResults_1254_20170828_LHC16q_pass1_CENT_wSDD.root");
    list[1] = (TList*) file1->Get("pPbCorrelations_FC");
    TDirectoryFile* df1=file1->Get("MultSelection");
  }

 if(woSDD){
   TFile*file2=new TFile("../resutl_20170828/AnalysisResults_1259_20170828_LHC16q_pass1_CENT_woSDD.root");
   list[2] = (TList*) file2->Get("pPbCorrelations_FC");
   TDirectoryFile* df2=file2->Get("MultSelection");
  }

 //LHC16t
 if(Fast){
   TFile*file3 =new TFile("../resutl_20170828/AnalysisResults_1258_20170828_LHC16t_pass1_FAST.root");
   list[3] = (TList*) file3->Get("pPbCorrelations_FC");
   TDirectoryFile* df3=file0->Get("MultSelection");
 }

  if(wSDD){
    TFile*file4 =new TFile("../resutl_20170828/AnalysisResults_1257_20170828_LHC16t_pass1_CENT_wSDD.root");
    list[4] = (TList*) file4->Get("pPbCorrelations_FC");
    TDirectoryFile* df4=file1->Get("MultSelection");
  }

 if(woSDD){
   TFile*file5=new TFile("../resutl_20170828/AnalysisResults_1256_20170828_LHC16t_pass1_CENT_woSDD.root");
   list[5] = (TList*) file5->Get("pPbCorrelations_FC");
   TDirectoryFile* df5=file2->Get("MultSelection");
  }

 const Int_t ncanvas=5;
 TCanvas*ch[ncanvas];
 for(Int_t i=0;i<ncanvas;i++){
   ch[i]=new TCanvas(Form("histcanvas_%d",i),Form("canvas_%d",i),600,400);
 }


 ch[4]->cd();
 TH1D* hh2[6];
 Float_t neve[6];
 Float_t alleve=0;
 for(Int_t i=0;i<6;i++){
   hh2[i]=drawhist(list[i],"fHist_Stat",kTRUE);
    hh2[i]->SetLineColor(color[i]);
    hh2[i]->SetMinimum(0);
    hh2[i]->SetLineWidth(2);
    SetHistoStyle1D(hh2[i],"Centrality(%)","Counts/Events","");
    hh2[i]->Draw("SAME");
    neve[i]=hh2[i]->GetBinContent(7);
    if(i!=1 && i!=4) alleve+=neve[i];
 }
  
 ch[0]->cd();
 TH1D* hh[6];
 TH1D* hh_clone[6];
 TH1D* hh_ratio[6];
 TH1D* hh_all;
 for(Int_t i=0;i<6;i++){
   hh[i]=drawhist(list[i],"fHistzvertex",kTRUE);
   hh[i]->SetLineColor(color[i]);
   hh[i]->SetLineWidth(2);
   hh[i]->GetXaxis()->SetRangeUser(-11,11);
   SetHistoStyle1D(hh[i],"V_{z}(cm)","Counts/Events","");
   hh[i]->Draw("SAME");
   hh_ratio[i]=(TH1D*)(hh[i]->Clone(Form("hh_ratio_%d",i)));
 }
 TLegend*leg=new TLegend(0.35,0.17,0.8,0.45,"","NDC");
 leg->SetTextSize(0.04);
 leg->SetFillColor(0);
 leg->SetBorderSize(0);
 leg->AddEntry(hh[0],"LHC16q(Fast)");
 leg->AddEntry(hh[1],"LHC16q(wSDD)");
 leg->AddEntry(hh[2],"LHC16q(woSDD)");
 leg->AddEntry(hh[3],"LHC16t(Fast)");
 leg->AddEntry(hh[4],"LHC16t(wSDD)");
 leg->AddEntry(hh[5],"LHC16t(woSDD)");
 leg->Draw("SAME");
 ch[1]->cd();
 TH1D* hh1[6];
 TH1D* hh1_ratio[6];
 for(Int_t i=0;i<6;i++){
   hh1[i]=drawhist(list[i],"fHistCentrality",kTRUE);
   hh1[i]->SetLineColor(color[i]);
   hh1[i]->SetMinimum(0);
   hh1[i]->SetLineWidth(2);
   SetHistoStyle1D(hh1[i],"Centrality(%)","Counts/Events","");
   hh1[i]->Draw("SAME");
   hh1_ratio[i]=(TH1D*)hh1[i]->Clone(Form("hh1_ratio_%d",i));
 }
 leg->Draw("SAME");
 
 
 ch[2]->cd();
 for(Int_t i=1;i<6;i++){
   hh_ratio[i]->Divide(hh_ratio[0]);
   SetHistoStyle1D(hh_ratio[i],"V_{Z}(cm)","ratio","");
   hh_ratio[i]->GetYaxis()->SetRangeUser(0.8,1.1);
   hh_ratio[i]->Draw("SAME");

 }
  TLegend*leg1=new TLegend(0.35,0.17,0.8,0.45,"","NDC");
 leg1->SetTextSize(0.04);
 leg1->SetFillColor(0);
 leg1->SetBorderSize(0);
 leg1->AddEntry(hh[1],"LHC16q(wSDD)/LHC16q(Fast)");
 leg1->AddEntry(hh[2],"LHC16q(woSDD)/LHC16q(Fast)");
 leg1->AddEntry(hh[3],"LHC16t(Fast)/LHC16q(Fast)");
 leg1->AddEntry(hh[4],"LHC16t(wSDD)/LHC16q(Fast)");
 leg1->AddEntry(hh[5],"LHC16t(woSDD)/LHC16q(Fast)");
 leg1->Draw("SAME");

 ch[3]->cd();
 for(Int_t i=1;i<6;i++){
   hh1_ratio[i]->Divide(hh1_ratio[0]);
   SetHistoStyle1D(hh1_ratio[i],"Centrality(%)","ratio","");
   hh1_ratio[i]->GetYaxis()->SetRangeUser(0.95,1.02);
   hh1_ratio[i]->Draw("SAME");
 }
  leg1->Draw("SAME");

  cout<<alleve<<endl;

 
 /*
 ch[2]->cd();
 compglobal(list[0],list[1],list[2],"fHistzvertex");
 ch[3]->cd();
 compglobal(list[0],list[1],list[2],"fHistCentrality");
 ch[4]->cd();
 compglobal(list[0],list[1],list[2],"fHist_Stat");
  ch[5]->cd();
 compglobal(list[3],list[4],list[5],"fHistzvertex");
 ch[6]->cd();
 compglobal(list[3],list[4],list[5],"fHistCentrality");
 ch[7]->cd();
 compglobal(list[3],list[4],list[5],"fHist_Stat");
 */

 
 
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

TH1D* drawhist(TList*list,char*name,Bool_t comp){
  if(!list) return;
  TH1D* hh=(TH1D*)(list->FindObject(name));
  Float_t nevent;
  if(name!="fHist_Stat"){
    nevent=hh->Integral(1,hh->GetNbinsX());
    if(comp)hh->Scale(1./nevent);
  }else{
    nevent=hh->GetBinContent(7);
  }
  Printf("%s,%f",name,nevent);
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
