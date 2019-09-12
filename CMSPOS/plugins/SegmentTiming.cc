#include "SegmentTiming.h"

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/ConsumesCollector.h"

#include <TROOT.h>
#include <TSystem.h>
#include <TFile.h>

//
// constructors and destructor
//
SegmentTiming::SegmentTiming(const edm::ParameterSet& iConfig) 
{
  edm::ConsumesCollector collector(consumesCollector());
  cscSegmentToken_ = consumes<CSCSegmentCollection>(edm::InputTag("cscSegments"));
  dtSegmentToken_ = consumes<DTRecSegment4DCollection>(edm::InputTag("dt4DSegments"));
}


SegmentTiming::~SegmentTiming()
{
  if (hFile!=0) {
    hFile->Close();
    delete hFile;
  }
}


//
// member functions
//

// ------------ method called to for each event  ------------
void
SegmentTiming::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  edm::Handle<CSCSegmentCollection> allSegmentsCSC;
  iEvent.getByToken(cscSegmentToken_, allSegmentsCSC);

  edm::Handle<DTRecSegment4DCollection> dtRecHits;
  iEvent.getByToken(dtSegmentToken_, dtRecHits);  

  // fill the ntuple here
  
  // when information for one segment is filled then fill it to the ntuple:
  t->Fill();  
}


// ------------ method called once each job just before starting event loop  ------------
void 
SegmentTiming::beginJob()
{
   hFile = new TFile( "segments.root", "recreate" );
   hFile->cd();

   t = new TTree("Segments", "Segments");
   
   // number of hits of different types in the segment
   // this number also signals which segment type is stored
   t->Branch("nHitsCSC", &nHitsCSC, "nHitsCSC/I");
   t->Branch("nHitsPhi", &nHitsPhi, "nHitsPhi/I");
   t->Branch("nHitsZed", &nHitsZed, "nHitsZed/I");
   // segment time
   t->Branch("time", &time, "time/D");
}

// ------------- write ntuple to file  ------------
void SegmentTiming::endJob() {

  hFile->cd();
  t->Write();
  hFile->Write();
  delete t;  
}


//define this as a plug-in
DEFINE_FWK_MODULE(SegmentTiming);
