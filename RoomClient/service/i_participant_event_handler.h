#pragma once

#include <memory>
#include <string>

namespace webrtc {
    class MediaStreamTrackInterface;
}

namespace vi {

class IParticipant;

class IParticipantEventHandler {
public:
    virtual ~IParticipantEventHandler() = default;

    virtual void onParticipantJoin(std::shared_ptr<IParticipant> participant) = 0;

    virtual void onParticipantLeave(std::shared_ptr<IParticipant> participant) = 0;

    virtual void onRemoteActiveSpeaker(std::shared_ptr<IParticipant> participant, int32_t volume) = 0;

    virtual void onDisplayNameChanged(std::shared_ptr<IParticipant> participant) = 0;

    virtual void onCreateRemoteVideoTrack(std::shared_ptr<IParticipant> participant, const std::string& tid, rtc::scoped_refptr<webrtc::MediaStreamTrackInterface> track) = 0;

    virtual void onRemoveRemoteVideoTrack(std::shared_ptr<IParticipant> participant, const std::string& tid, rtc::scoped_refptr<webrtc::MediaStreamTrackInterface> track) = 0;

    virtual void onRemoteAudioStateChanged(std::shared_ptr<IParticipant> participant, bool muted) = 0;

    virtual void onRemoteVideoStateChanged(std::shared_ptr<IParticipant> participant, bool muted) = 0;
};

}
