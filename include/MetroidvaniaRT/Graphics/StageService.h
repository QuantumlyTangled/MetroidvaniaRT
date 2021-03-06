#ifndef METROIDVANIART_STAGESERVICE_H
#define METROIDVANIART_STAGESERVICE_H

#ifndef METROIDVANIART_H
#error Please do not include this directly. Use the centralised header (MetroidvaniaRT.h) instead!
#endif

namespace MetroidvaniaRT::Graphics {
  struct findingComparator {
    bool operator()(const IdentificationInformation& x, const IdentificationInformation& y) const {
      return (x.id > y.id);
    }
  };

  class StageService {

  protected:
    MetroidvaniaRunner* const _runner;

  public:
    std::map<IdentificationInformation, std::unique_ptr<Stage>, findingComparator> stages;

    StageService* addStage(std::unique_ptr<Stage> stage);

    Stage* getStage(int _id);
    Stage* getStage(const std::string& _name);

    template<typename RenderedObj, typename std::enable_if<std::is_base_of<NovelRT::Graphics::RenderObject, RenderedObj>::value>::type * = nullptr>
    StageService* addStagePlatform(const std::string& stageName, std::unique_ptr<Platform<RenderedObj>> platform) {
      auto stage = getStage(stageName);
      stage->addPlatform(std::move(platform));
      return this;
    }
    template<typename RenderedObj, typename std::enable_if<std::is_base_of<NovelRT::Graphics::RenderObject, RenderedObj>::value>::type * = nullptr>
    StageService* addStagePlatform(int stageId, std::unique_ptr<Platform<RenderedObj>> platform) {
      auto stage = getStage(stageId);
      stage->addPlatform(std::move(platform));
      return this;
    }

    Stage* createStage(int stageId, bool force = false);
    Stage* createStage(const std::string& stageName, bool force = false);

    Stage* renderStage(int stageId);
    Stage* renderStage(const std::string& stageName);

    void initiateRenderLoopStage(int stageId);
    void initiateRenderLoopStage(const std::string& stageName);

    StageService(MetroidvaniaRunner* const runner);
  };
}

#endif // METROIDVANIART_STAGESERVICE_H
