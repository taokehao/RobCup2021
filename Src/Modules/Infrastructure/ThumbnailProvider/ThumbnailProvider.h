/**
 * @file ThumbnailProvider.h
 *
 * Declares a module which calculated a colored or grayscaled thumbnail image.
 *
 * @author Alexis Tsogias
 * @author <a href="mailto:jesse@tzi.de">Jesse Richter-Klug</a>
 * @author Felix Thielke
 */

#pragma once

#include "Tools/Module/Module.h"
#include "Representations/Infrastructure/CameraInfo.h"
#include "Representations/Infrastructure/CameraImage.h"
#include "Representations/Infrastructure/Thumbnail.h"
#include "Representations/Perception/ImagePreprocessing/ECImage.h"

MODULE(ThumbnailProvider,
{,
  REQUIRES(CameraImage),
  REQUIRES(ECImage),
  REQUIRES(CameraInfo),
  PROVIDES_WITHOUT_MODIFY(Thumbnail),
  LOADS_PARAMETERS(
  {,
    (unsigned) downScales,
    (bool) useUpperSize,
    (Thumbnail::Mode) mode,
  }),
});

class ThumbnailProvider : public ThumbnailProviderBase
{
private:
  TImage<PixelTypes::ColoredPixel> shrinkedColors;

  void shrinkY(const unsigned int downScales, const TImage<PixelTypes::GrayscaledPixel>& src, TImage<PixelTypes::GrayscaledPixel>& dest) const;
  void shrinkColors(const unsigned int downScales, const TImage<PixelTypes::ColoredPixel>& src, TImage<PixelTypes::ColoredPixel>& dest) const;
  void shrinkUV(const unsigned int downScales, const CameraImage& src, TImage<unsigned short>& dest) const;

  void combineGrayscaleAndColors(const TImage<PixelTypes::GrayscaledPixel>& y, const TImage<PixelTypes::ColoredPixel>& c, TImage<PixelTypes::GrayscaledPixel>& dest) const;

public:
  void update(Thumbnail& thumbnail) override;
};
