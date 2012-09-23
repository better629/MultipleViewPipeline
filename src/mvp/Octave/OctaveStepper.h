/// \file OctaveStepper.h
///
/// TODO: Write doc
///

#ifndef __MVP_OCTAVE_STEPPER_H__
#define __MVP_OCTAVE_STEPPER_H__

namespace mvp {
namespace octave {


}} // namespace octave, mvp

#include <mvp/Octave/oct-mvpobj.h>

#include <mvp/Algorithm/Stepper/StupidStepper.h>

octave_value_list MvpStepper(octave_value_list const& args, int nargout) {
  if (args.length() == 0) {
    return octave_value(new octave_mvpobj_ref(new octave_mvpobj_impl<mvp::algorithm::Stepper>()));
  }

  mvp::algorithm::Stepper *stepper = NULL;
  std::string name = args(0).string_value();

  if (name == "StupidStepper") {
    stepper = new mvp::algorithm::StupidStepper();
  }

  if (stepper) {
    return octave_value(new octave_mvpobj_ref(new octave_mvpobj_wrap<mvp::algorithm::Stepper>(stepper, true)));
  } else {
    error("`%s' is not a valid MvpStepper", name.c_str());
    return octave_value();
  }
}

octave_value mvpobj_wrap_function(mvp::algorithm::Stepper *obj, std::string const& method, octave_value_list const& args) {
  std::cout << "wrapping stepper->" << method << "(" << args.length() << ")" << std::endl;
  return octave_value();
}

#endif