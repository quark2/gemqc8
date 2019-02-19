#ifndef EventFilter_GEMRawToDigi_AMC13Event_h
#define EventFilter_GEMRawToDigi_AMC13Event_h
#include <vector>
#include <string>
#include <sstream>
#include "AMCdata.h"

namespace gem {
  
  union CDFHeader {
    CDFHeader (uint64_t x=0) : word(x) {}

    uint64_t word;
    struct {
      uint64_t fov       : 8;  // not used
      uint64_t sourceId  : 12; // FED number assigned by CDAQ
      uint64_t bxId      : 12; // Bunch crossing 0...3563
      uint64_t lv1Id     : 24; // Level 1 ID (hardware event number)
      uint64_t eventType : 4;  // Event Type (1 for normal, 2 for calibration)
      uint64_t cb5       : 4;  // 0x5
    };
  };

  union AMC13Header {
    AMC13Header(uint64_t x=0) : word(x) {}

    uint64_t word;
    struct {
      uint64_t cb0       : 4;  // 0x0
      uint64_t orbitN    : 32; // Orbit Number
      uint64_t reserved0 : 16; // reserved
      uint64_t nAMC      : 4;  // Number of AMCs following (0 to 12)
      uint64_t calType   : 4;  // Calibration event type
      uint64_t uFov      : 4;  // Format version: 0x1
    };
  };

  union AMC13DataDef {
    AMC13DataDef(uint64_t x=0) : word(x) {}

    uint64_t word;
    struct {
      uint64_t boardId    : 16; // board id
      uint64_t amcNo      : 4;  // amcNo
      uint64_t blkSeqNo   : 8;  // block sequence no
      uint64_t cb0        : 4;  // 0x0
      uint64_t dataSize   : 24; // amc payload size
      uint64_t endBits8   : 8;  // c,v,p,e,s,m,l,?
    };
  };

  union AMC13Trailer {
    AMC13Trailer(uint64_t x=0) : word(x) {}

    uint64_t word;
    struct {
      uint64_t bxIdT     : 12; // bx id
      uint64_t lv1IdT    : 8;  // level 1 id
      uint64_t blkN      : 8;  // block number
      uint64_t cb0       : 4;  // 0x0
      uint64_t crc32     : 32; // Overall CRC (first 32 bits)
    };
  };

  union CDFTrailer {
    CDFTrailer(uint64_t x=0) : word(x) {}

    uint64_t word;
    struct {
      uint64_t trdd      : 4;  // $,$,t,r
      uint64_t tts       : 4;  // tts (first 4 bits)
      uint64_t evtStat   : 4;  // event status
      uint64_t cfxx      : 4;  // x,x,f,c
      uint64_t crcCDF    : 16; // CDF crc (first 16 bits)
      uint64_t evtLength : 24; // event length
      uint64_t evtType   : 4;  // event type
      uint64_t cbA       : 4;  // 0xA (first 4 bits)
    };
  };

  class AMC13Event
  {
    
  public:
    AMC13Event() {}
    ~AMC13Event() {amcHeaders_.clear(); amcs_.clear();}

    void setCDFHeader(uint64_t word) { cdfh_ = word;}
    void setCDFHeader(uint8_t Evt_ty, uint32_t LV1_id, uint16_t BX_id, uint16_t Source_id) {
      CDFHeader u;
      u.cb5 = 0x5;
      u.eventType = Evt_ty;
      u.lv1Id = LV1_id;
      u.bxId = BX_id;
      u.sourceId = Source_id;
      u.fov = 0; // not used
      cdfh_ = u.word;
    };
    uint64_t getCDFHeader() const { return cdfh_;}

    void setAMC13Header(uint64_t word) { amc13h_ = word;}
    void setAMC13Header(uint8_t CalTyp, uint8_t nAMC, uint32_t OrN) {
      AMC13Header u;
      u.uFov = 0; // format version # FIX ME
      u.calType = CalTyp;
      u.nAMC = nAMC;
      u.reserved0 = 0;
      u.orbitN = OrN;
      u.cb0 = 0x0;
      amc13h_ = u.word;
    };
    uint64_t getAMC13Header() const { return amc13h_;}

    void setAMC13Trailer(uint64_t word) { amc13t_ = word;}
    void setAMC13Trailer(uint8_t Blk_NoT, uint8_t LV1_idT, uint16_t BX_idT) {
      AMC13Trailer u;
      u.crc32 = 0; // FIX ME
      u.blkN = Blk_NoT;
      u.lv1IdT = LV1_idT;
      u.bxIdT = BX_idT;
      amc13t_ = u.word;
    };
    uint64_t getAMC13Trailer() const { return amc13t_;}

    void setCDFTrailer(uint64_t word) { cdft_ = word;}
    void setCDFTrailer(uint32_t EvtLength) {
      CDFTrailer u;
      u.cbA = 0xA;
      u.evtType = 0; // FIX ME
      u.evtLength = EvtLength;
      u.crcCDF = 0; // FIX ME
      u.cfxx = 0; // FIX ME
      u.evtStat = 0; // event status # FIX ME
      u.tts = 0;
      u.trdd = 0;
      cdft_ = u.word;
    };
    uint64_t getCDFTrailer() const { return cdft_; }

    uint16_t bxId() const {return CDFHeader{cdfh_}.bxId;}
    uint32_t lv1Id() const {return CDFHeader{cdfh_}.lv1Id;}
    uint16_t sourceId() const {return CDFHeader{cdfh_}.sourceId;}

    uint32_t get_fov() const {return (uint32_t)CDFHeader{cdfh_}.fov;}
    uint32_t get_sourceId() const {return (uint32_t)CDFHeader{cdfh_}.sourceId;}
    uint32_t get_bxId() const {return (uint32_t)CDFHeader{cdfh_}.bxId;}
    uint32_t get_lv1Id() const { return (uint32_t)CDFHeader{cdfh_}.lv1Id;}
    uint32_t get_eventType() const {return (uint32_t)CDFHeader{cdfh_}.eventType;}
    uint32_t get_cb5() const {return (uint32_t)CDFHeader{cdfh_}.cb5;}

    uint8_t  nAMC() const {return AMC13Header{amc13h_}.nAMC;}

    uint32_t get_cb0() const {return (uint32_t)AMC13Header{amc13h_}.cb0;}
    uint32_t get_orbitN() const {return (uint32_t)AMC13Header{amc13h_}.orbitN;}
    uint32_t get_reserved0() const {return (uint32_t)AMC13Header{amc13h_}.reserved0;}
    uint32_t get_nAMC() const {return (uint32_t)AMC13Header{amc13h_}.nAMC;}
    uint32_t get_calType() const {return (uint32_t)AMC13Header{amc13h_}.calType;}
    uint32_t get_uFov() const {return (uint32_t)AMC13Header{amc13h_}.uFov;}

    const std::vector<uint64_t> * getAMCheaders() const {return &amcHeaders_;}
    void addAMCheader(uint64_t word) {amcHeaders_.push_back(word);};
    void addAMCheader(uint32_t AMC_size, uint8_t Blk_No, uint8_t AMC_No, uint16_t BoardID) {
      // AMC Header word 
      // 55 - 32  | 27 - 20 | 19 - 16 | 15 - 0  |
      // AMC_size | Blk_No  | AMC_No  | BoardID |  
      //uint64_t word =
      //  (static_cast<uint64_t>(AMC_size & 0x00ffffff) << 32) |
      //  (static_cast<uint64_t>(Blk_No & 0xff) << 20) |
      //  (static_cast<uint64_t>(AMC_No & 0x0f) << 16) |
      //  (static_cast<uint64_t>(BoardID & 0xffff));
      AMC13DataDef u(0);
      u.dataSize = AMC_size;
      u.blkSeqNo = Blk_No;
      u.amcNo = AMC_No;
      u.boardId = BoardID;
      amcHeaders_.push_back(u.word);
    };

    uint32_t get_boardId(int i) const {return (uint32_t)AMC13DataDef{amcHeaders_[i]}.boardId;}
    uint32_t get_amcNo(int i) const {return (uint32_t)AMC13DataDef{amcHeaders_[i]}.amcNo;}
    uint32_t get_blkSeqNo(int i) const {return (uint32_t)AMC13DataDef{amcHeaders_[i]}.blkSeqNo;}
    uint32_t get_cb0(int i) const {return (uint32_t)AMC13DataDef{amcHeaders_[i]}.cb0;}
    uint32_t get_dataSize(int i) const {return (uint32_t)AMC13DataDef{amcHeaders_[i]}.dataSize;}
    uint32_t get_endBits8(int i) const {return (uint32_t)AMC13DataDef{amcHeaders_[i]}.endBits8;}

    uint32_t get_bxIdT() const {return (uint32_t)AMC13Trailer{amc13t_}.bxIdT;}
    uint32_t get_lv1IdT() const {return (uint32_t)AMC13Trailer{amc13t_}.lv1IdT;}
    uint32_t get_blkSeqNoT() const {return (uint32_t)AMC13Trailer{amc13t_}.blkN;}
    uint32_t get_cb0T() const {return(uint32_t)AMC13Trailer{amc13t_}.cb0;}

    uint32_t get_trddT() const {return (uint32_t)CDFTrailer{cdft_}.trdd;}
    uint32_t get_evtTypeT() const {return (uint32_t)CDFTrailer{cdft_}.evtType;}
    uint32_t get_evtLenT() const {return (uint32_t)CDFTrailer{cdft_}.evtLength;}
    uint32_t get_cbAT() const {return (uint32_t)CDFTrailer{cdft_}.cbA;}

    const std::vector<AMCdata> * getAMCpayloads() const {return &amcs_;}   
    void addAMCpayload(const AMCdata& a) {amcs_.push_back(a);}

    std::string getCDFHeader_str() const {
      CDFHeader u;
      u.word = cdfh_;
      std::stringstream ss;
      ss << "CDFHeader: fov=" << (uint32_t)(u.fov) << " sourceId=" << (uint32_t)(u.sourceId) << " bxId=" << (uint32_t)(u.bxId) << " lv1Id=" << (uint32_t)(u.lv1Id) << " eventType=" << (uint32_t)(u.eventType) << " cb5=" << (uint32_t)(u.cb5);
      return ss.str();
    };
    std::string getCDFTrailer_str() const {
      CDFTrailer u;
      u.word = cdft_;
      std::stringstream ss;
      ss << "CDFTrailer: trdd=" << (uint32_t)(u.trdd) << " tts=" << (uint32_t)(u.tts) << " evtStat=" << (uint32_t)(u.evtStat) << " cfxx=" << (uint32_t)(u.cfxx) << " crcCDF=" << (uint32_t)(u.crcCDF) << " evtLength=" << (uint32_t)(u.evtLength) << " evtType=" << (uint32_t)(u.evtType) << " cbA=" << (uint32_t)(u.cbA);
      return ss.str();
    };
    std::string getAMC13Header_str() const {
      AMC13Header u;
      u.word = amc13h_;
      std::stringstream ss;
      ss << "AMC13Header: cb0=" << (uint32_t)(u.cb0) << " orbitN=" << (uint32_t)(u.orbitN) << " reserved0=" << (uint32_t)(u.reserved0) << " nAMC=" << (uint32_t)(u.nAMC) << " calType=" << (uint32_t)(u.calType) << " uFov=" << (uint32_t)(u.uFov);
      return ss.str();
    };
    std::string getAMC13Trailer_str() const {
      AMC13Trailer u;
      u.word = amc13t_;
      std::stringstream ss;
      ss << "AMC13Trailer: bxIdT=" << (uint32_t)(u.bxIdT) << " lv1IdT=" << (uint32_t)(u.lv1IdT) << " blkN=" << (uint32_t)(u.blkN) << " crc32=" << (uint32_t)(u.crc32);
      return ss.str();
    };
    std::string getAMC13DataDef_str(int i) const {
      AMC13DataDef d = amcHeaders_.at(i);
      std::stringstream ss;
      ss << "AMC13DataDef: boardId=" << (uint32_t)(d.boardId) << " amcNo=" << (uint32_t)(d.amcNo) << " blkSeqNo=" << (uint32_t)(d.blkSeqNo) << " cb0=" << (uint32_t)(d.cb0) << " dataSize=" << (uint32_t)(d.dataSize) << " endBits8" << (uint32_t)(d.endBits8);
      return ss.str();
    };
    
  private:

    uint64_t cdfh_;
    uint64_t amc13h_;
    uint64_t amc13t_;
    uint64_t cdft_;

    // AMC headers
    std::vector<uint64_t> amcHeaders_;
    // AMCs payload
    std::vector<AMCdata> amcs_;

    //CDFHeader cdfh_;
    //AMC13Header amc13h_;
    //AMC13Trailer amc13t_;
    //CDFTrailer cdft_;
      
  };
}
#endif
