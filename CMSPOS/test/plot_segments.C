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

  // book histograms
  TH1D *hi_csctime =   new TH1D("hi_csctime","CSC Segment Time",80 ,-200,200);

  // Loop over all entries of the TTree
  myReader.SetEntry(0);
  while (myReader.Next()) {
    std::cout << " segment has " << *HitsCSC << " CSC hits " << std::endl;
    
    // fill histograms here
  }
  
  // draw histograms here
}
