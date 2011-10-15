#include <gtest/gtest.h>
#include <test/Helpers.h>
#include <mvp/MVPTileProcessor.h>
#include <mvp/MVPWorkspace.h>

using namespace std;
using namespace vw;
using namespace vw::test;
using namespace vw::cartography;
using namespace vw::platefile;
using namespace mvp;

TEST(MVPTileProcessor, process) {
  MVPWorkspace work("", "", PlateGeoReference(Datum("D_MOON")), MVPAlgorithmSettings());
  work.add_image_pattern(SrcName("synth.%d.pinhole"), SrcName("synth.%d.tif"), Vector2i(0, 3));

  EXPECT_EQ(work.num_images(), 4);

  int level = work.equal_density_level();
  Vector2 col_row = work.tile_work_area(work.equal_density_level()).min();

  MVPJobRequest job = work.assemble_job(col_row[0], col_row[1], level);

  MVPTileProcessor proc(job);

  MVPTileResult result = proc.process();

  EXPECT_EQ(result.post_height(0, 0), 0);
}

TEST(MVPTileProcessor, offset_georef) {
  GeoReference geo = PlateGeoReference().tile_georef(1, 2, 3);
  GeoReference crop_geo = offset_georef(geo, 100, 200);

  EXPECT_VECTOR_EQ(geo.pixel_to_lonlat(Vector2(100, 200)), crop_geo.pixel_to_lonlat(Vector2(0, 0)));
  EXPECT_VECTOR_EQ(geo.pixel_to_lonlat(Vector2(120, 230)), crop_geo.pixel_to_lonlat(Vector2(20, 30)));
}