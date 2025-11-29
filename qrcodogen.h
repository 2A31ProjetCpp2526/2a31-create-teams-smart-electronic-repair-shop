/*
 * QR Code generator library (C++)
 *
 * Copyright (c) Project Nayuki. (MIT License)
 * https://www.nayuki.io/page/qr-code-generator-library
 */

#pragma once

#include <array>
#include <cstdint>
#include <stdexcept>
#include <string>
#include <vector>

namespace qrcodegen {

/*
 * A segment of character/binary/control data in a QR Code symbol.
 * Instances of this class are immutable.
 */
class QrSegment final {

public:
    /*---- Helper enumeration ----*/
    class Mode final {

    public:
        static const Mode NUMERIC;
        static const Mode ALPHANUMERIC;
        static const Mode BYTE;
        static const Mode KANJI;
        static const Mode ECI;

        int getModeBits() const;
        int numCharCountBits(int ver) const;

    private:
        int modeBits;
        int numBitsCharCount[3];

        Mode(int mode, int cc0, int cc1, int cc2);
    };

    /*---- Static factory functions (mid level) ----*/

    static QrSegment makeBytes(const std::vector<std::uint8_t> &data);
    static QrSegment makeNumeric(const char *digits);
    static QrSegment makeAlphanumeric(const char *text);
    static std::vector<QrSegment> makeSegments(const char *text);
    static QrSegment makeEci(long assignVal);

    /*---- Static helpers ----*/
    static bool isNumeric(const char *text);
    static bool isAlphanumeric(const char *text);

    /*---- Constructors (low level) ----*/

    QrSegment(const Mode &md, int numCh, const std::vector<bool> &dt);
    QrSegment(const Mode &md, int numCh, std::vector<bool> &&dt);

    /*---- Methods ----*/

    const Mode &getMode() const;
    int getNumChars() const;
    const std::vector<bool> &getData() const;

    static int getTotalBits(const std::vector<QrSegment> &segs, int version);

private:
    const Mode *mode;
    int numChars;
    std::vector<bool> data;

    static const char *ALPHANUMERIC_CHARSET;
};


/*
 * A QR Code symbol, which is a type of two-dimension barcode.
 */
class QrCode final {

public:
    /*---- Helper enumeration ----*/
    enum class Ecc {
        LOW = 0,
        MEDIUM,
        QUARTILE,
        HIGH,
    };

    /*---- Factory functions ----*/

    static QrCode encodeText(const char *text, Ecc ecl);
    static QrCode encodeBinary(const std::vector<std::uint8_t> &data, Ecc ecl);
    static QrCode encodeSegments(const std::vector<QrSegment> &segs, Ecc ecl,
                                 int minVersion = 1, int maxVersion = 40,
                                 int mask = -1, bool boostEcl = true);

    /*---- Constants ----*/
    static constexpr int MIN_VERSION = 1;
    static constexpr int MAX_VERSION = 40;

    /*---- Public instance methods ----*/

    int  getVersion() const;
    int  getSize() const;
    Ecc  getErrorCorrectionLevel() const;
    int  getMask() const;
    bool getModule(int x, int y) const;

private:
    // scalar params
    int version;
    int size;
    Ecc errorCorrectionLevel;
    int mask;

    // grids
    std::vector<std::vector<bool>> modules;
    std::vector<std::vector<bool>> isFunction;

    // constructor (low level)
    QrCode(int ver, Ecc ecl, const std::vector<std::uint8_t> &dataCodewords, int msk);

    // static helpers
    static int  getFormatBits(Ecc ecl);
    static int  getNumRawDataModules(int ver);
    static int  getNumDataCodewords(int ver, Ecc ecl);
    static std::vector<std::uint8_t> reedSolomonComputeDivisor(int degree);
    static std::vector<std::uint8_t> reedSolomonComputeRemainder(const std::vector<std::uint8_t> &data,
                                                                 const std::vector<std::uint8_t> &divisor);
    static std::uint8_t reedSolomonMultiply(std::uint8_t x, std::uint8_t y);
    static bool getBit(long x, int i);

    // drawing helpers
    void drawFunctionPatterns();
    void drawFormatBits(int msk);
    void drawVersion();
    void drawFinderPattern(int x, int y);
    void drawAlignmentPattern(int x, int y);
    void setFunctionModule(int x, int y, bool isDark);
    bool module(int x, int y) const;
    std::vector<std::uint8_t> addEccAndInterleave(const std::vector<std::uint8_t> &data) const;
    void drawCodewords(const std::vector<std::uint8_t> &data);
    void applyMask(int msk);
    long getPenaltyScore() const;
    std::vector<int> getAlignmentPatternPositions() const;

    // finder penalty
    int  finderPenaltyCountPatterns(const std::array<int,7> &runHistory) const;
    int  finderPenaltyTerminateAndCount(bool currentRunColor, int currentRunLength,
                                       std::array<int,7> &runHistory) const;
    void finderPenaltyAddHistory(int currentRunLength, std::array<int,7> &runHistory) const;

    // penalty constants
    static const int PENALTY_N1;
    static const int PENALTY_N2;
    static const int PENALTY_N3;
    static const int PENALTY_N4;

    static const std::int8_t ECC_CODEWORDS_PER_BLOCK[4][41];
    static const std::int8_t NUM_ERROR_CORRECTION_BLOCKS[4][41];
};


/*---- Exception ----*/

class data_too_long : public std::length_error {
public:
    explicit data_too_long(const std::string &msg);
};


/*---- BitBuffer ----*/

class BitBuffer final : public std::vector<bool> {

public:
    BitBuffer();
    void appendBits(std::uint32_t val, int len);
};

} // namespace qrcodegen
