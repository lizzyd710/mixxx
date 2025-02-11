#pragma once

#include "sources/soundsourceprovider.h"

namespace ModPlug {
#include <libmodplug/modplug.h>
}

#include <vector>

namespace mixxx {

// Class for reading tracker files using libmodplug.
// The whole file is decoded at once and saved
// in RAM to allow seeking and smooth operation in Mixxx.
class SoundSourceModPlug final : public SoundSource {
  public:
    static constexpr int kChannelCount = 2;
    static constexpr int kSampleRate = 44100;
    static constexpr int kBitsPerSample = 16;

    // apply settings for decoding
    static void configure(unsigned int bufferSizeLimit,
            const ModPlug::ModPlug_Settings& settings);

    explicit SoundSourceModPlug(const QUrl& url);
    ~SoundSourceModPlug() override;

    std::pair<ImportResult, QDateTime> importTrackMetadataAndCoverImage(
            TrackMetadata* pTrackMetadata,
            QImage* pCoverArt) const override;

    void close() override;

  protected:
    ReadableSampleFrames readSampleFramesClamped(
            const WritableSampleFrames& sampleFrames) override;

  private:
    OpenResult tryOpen(
            OpenMode mode,
            const OpenParams& params) override;

    static unsigned int s_bufferSizeLimit; // max track buffer length (bytes)

    ModPlug::ModPlugFile* m_pModFile; // modplug file descriptor
    QByteArray m_fileBuf;             // original module file data

    typedef std::vector<SAMPLE> ModSampleBuffer;
    ModSampleBuffer m_sampleBuf;
};

class SoundSourceProviderModPlug : public SoundSourceProvider {
  public:
    static const QString kDisplayName;

    QString getDisplayName() const override {
        return kDisplayName;
    }

    QStringList getSupportedFileTypes() const override;

    SoundSourcePointer newSoundSource(const QUrl& url) override {
        return newSoundSourceFromUrl<SoundSourceModPlug>(url);
    }
};

} // namespace mixxx
