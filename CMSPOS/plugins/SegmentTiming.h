#ifndef SegmentTiming_H
#define SegmentTiming_H

// Base Class Headers
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"

#include "DataFormats/DTRecHit/interface/DTRecSegment4DCollection.h"
#include "DataFormats/CSCRecHit/interface/CSCSegmentCollection.h"

#include <TTree.h>

using namespace std;
using namespace edm;

class SegmentTiming : public edm::EDAnalyzer {
public: 

  explicit SegmentTiming(const edm::ParameterSet&);
  ~SegmentTiming();

private:
  virtual void beginJob() ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;

  // ----------member data ---------------------------
  string out, open;

  edm::EDGetTokenT<CSCSegmentCollection> cscSegmentToken_;
  edm::EDGetTokenT<DTRecSegment4DCollection> dtSegmentToken_;

  TFile* hFile;
  TTree* t;
  
  // ntuple content
  int nHitsCSC;
  int nHitsPhi;
  int nHitsZed;
  double time;

};
#endif
