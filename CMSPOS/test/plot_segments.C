#include <iostream>
#include <TH1.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>

void plot_segments() {

  TFile *file = TFile::Open("segments.root");
  if (!file || file->IsZombie()) {
    return;
  }

  TTreeReader myReader("Segments",file);

  TTreeReaderValue<int>   nHitsPhi(myReader, "nHitsPhi");
  TTreeReaderValue<int>   nHitsZed(myReader, "nHitsZed");
  TTreeReaderValue<int>   nHitsCSC(myReader, "nHitsCSC");
  TTreeReaderValue<double> time(myReader, "time");

  TH1D *hi_dtphitime =   new TH1D("hi_dtphitime","DT Segment Time (Phi projection)",100 ,-200,200);
  TH1D *hi_dtzedtime =   new TH1D("hi_dtzedtime","DT Segment Time (Zed projection)",100 ,-200,200);
  TH1D *hi_csctime =   new TH1D("hi_csctime","CSC Segment Time",100 ,-200,200);

  // Loop over all entries of the TTree
  myReader.SetEntry(0);
  while (myReader.Next()) {
    if (*nHitsPhi>0) hi_dtphitime->Fill(*time);
    if (*nHitsZed>0) hi_dtzedtime->Fill(*time);
    if (*nHitsCSC>0) hi_csctime->Fill(*time);
  }

  TCanvas *c1 = new TCanvas("c1","Segments",300,100,1200,800);

  c1->Divide(3,1);

  c1->cd(1);
  gPad->SetGridx(1);
  gPad->SetGridy(1);
  gPad->SetLogy(1);
  hi_dtphitime->DrawCopy();

  c1->cd(2);
  gPad->SetGridx(1);
  gPad->SetGridy(1);
  gPad->SetLogy(1);
  hi_dtzedtime->DrawCopy();

  c1->cd(3);
  gPad->SetGridx(1);
  gPad->SetGridy(1);
  gPad->SetLogy(1);
  hi_csctime->DrawCopy();
}
