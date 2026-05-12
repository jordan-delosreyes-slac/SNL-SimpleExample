// -*-Mode: C++;-*-

#ifndef __INTERNAL_TESTS_LAYERS_CIFAR10_CIFAR10_SNL_HH__
#define __INTERNAL_TESTS_LAYERS_CIFAR10_CIFAR10_SNL_HH__

/* ---------------------------------------------------------------------- *//*!

  \file   internal/tests/layers/cifar10/cifar10-snl.hh
  \brief  Cifar10 (small version) test network
  \author JJRussell - russell@slac.stanford.edu

  \par
   This file is part of the ML_AI software platform. It is subject to
   the license terms in the LICENSE.txt file found in the top-level
   directory of this distribution and at:

   \verbatim
     https://confluence.slac.stanford.edu/display/ppareg/LICENSE.html.
   \endverbatim

\* ---------------------------------------------------------------------- */




/* ---------------------------------------------------------------------- *\
 *
 * HISTORY
 * -------
 *
 * DATE       WHO WHAT
 * ---------- --- ---------------------------------------------------------
 * 2025.10.15 jjr Created
 *
\* ---------------------------------------------------------------------- */



// ---------------------------------------------------------------
// Should only include those layers, activators and types that are
// actually used.  Including more can increase compilation time.
// ---------------------------------------------------------------
#include "snl/parameters/Conv2D-Parameters.hh"
#include "snl/parameters/MaxPooling2D-Parameters.hh"
#include "snl/parameters/Dense2D-Parameters.hh"

#include "snl/activator/Relu.hh"
#include "snl/activator/Softmax.hh"

#include "snl/support/Standard.hh"


/* ====================================================================== */
namespace cifar10   {
/* ---------------------------------------------------------------------- */

   
// -------------------------------------------------------------------
// This section is purely a matter of taste in coding readability
// There is nothing fundamental here.  One could easily specify these
// values and types directly in the layer parameter definitions.
// -------------------------------------------------------------------

// ----------
// Shorthands
// ----------
static constexpr auto PrtLo  = snl::printer::Level::Lo;
static constexpr auto PrtMed = snl::printer::Level::Med;
static constexpr auto PrtHi  = snl::printer::Level::Hi;

using SrcType   = float;
using SrcStream = snl::Stream<SrcType, snl::Shape<32,32,3>>;

using PrintMin  = snl::printer::Options<PrtLo, PrtLo, PrtMed>;

// -----------------------------------
// Types of all kernel weights, biases
// -----------------------------------
using Type     = float;
   
/* ====================================================================== */
using Layer0 = snl::parameters::Conv2D
        <snl::LayerPosition::First, // First layer 
         SrcStream,                 // Input stream
         2,3,3,Type,                // KERNEL  :  NFILTERS, NCOL, NROWS, type
         1,1,                       // STRIDE  :  NROWS, NCOLS
         snl::Padding::Valid,       // PADDING
         1,1,                       // DILATION: NROWS, NCOLS
         1,                         // GROUPS,
         snl::activator::Relu<>,    // ACTIVATOR
         Type,                      // BIAS_TYPE
         snl::datatype::Auto,       // DST_TYPE,
         PrintMin
         >;
/* ---------------------------------------------------------------------- */
/* END: Layer0                                                            */
/* ====================================================================== */


/* ====================================================================== */
using Layer1 = snl::parameters::MaxPooling2D
        <snl::LayerPosition::Middle, 
         snl::SrcStream<Layer0>,     // Input stream
         2,2,                        // POOLING:  NROWS, NCOL
         2,2,                        // STRIDE :  NROWS, NCOLS,
         snl::Padding::Valid,        // PADDING
         snl::datatype::Auto,        // DST_TYPE,
         PrintMin
       >;
/* ---------------------------------------------------------------------- */
/* END: Layer1                                                            */
/* ====================================================================== */


/* ====================================================================== */
using Layer2 = snl::parameters::Conv2D
        <snl::LayerPosition::Middle, 
         snl::SrcStream<Layer1>,     // Input Stream
         4,3,3,Type,                 // KERNEL  :  NFILTERS, NROWS, NCOLS,Type
         1,1,                        // STRIDE  :  NROWS, NCOLS
         snl::Padding::Valid,        // PADDING 
         1,1,                        // DILATION: NROWS, NCOLS
         1,                          // GROUPS
         snl::activator::Relu<>,     // ACTIVATOR
         Type,                       // BIAS_TYPE
         snl::datatype::Auto,        // DST_TYPE
         PrintMin
         >;
/* ---------------------------------------------------------------------- */
/* END: Layer2                                                            */
/* ====================================================================== */


/* ====================================================================== */
using Layer3 = snl::parameters::MaxPooling2D
        <snl::LayerPosition::Middle,
         snl::SrcStream<Layer2>,      // Input Stream
         2,2,                         // POOLING:  NROWS, NCOLS
         2,2,                         // STRIDE :  NROWS, NCOLS
         snl::Padding::Valid,         // PADDING
         snl::datatype::Auto,         // DST_TYPE
         PrintMin
         >;
/* ---------------------------------------------------------------------- */
/* END: Layer3                                                            */
/* ====================================================================== */


/* ====================================================================== */
using Layer4 = snl::parameters::Conv2D
        <snl::LayerPosition::Middle, 
         snl::SrcStream<Layer3>,     // Input Stream
         8,3,3,Type,                 // KERNEL  :  NFILTERS, NROWS, NCOLS,Type
         1,1,                        // STRIDE  : NROWS, NCOLS
         snl::Padding::Valid,        // PADDING 
         1,1,                        // DILATION: NROWS, NCOLS
         1,                          // GROUPS
         snl::activator::Relu<>,     // ACTIVATOR
         Type,                       // BIAS_TYPE
         snl::datatype::Auto,        // DST_TYPE,
         PrintMin
         >;
/* ---------------------------------------------------------------------- */
/* END: Layer4                                                            */
/* ====================================================================== */


/* ====================================================================== */
using Layer5 = snl::parameters::Dense
        <snl::LayerPosition::Middle,  // 4th Middle layer
         snl::SrcStream<Layer4>,      // Input stream
         true,                        // Flatten input
         25,                          // Number of output colums
         Type,                        // WEIGHT_TYPE,
         snl::activator::Relu<>,      // ACTIVATOR,
         Type,                        // BIAS_TYPE,
         snl::datatype::Auto,         // DST_TYPE
         PrintMin
         >;
/* ---------------------------------------------------------------------- */
/* END: namespace layer5                                                  */
/* ====================================================================== */


/* ====================================================================== */
using Layer6 = snl::parameters::Dense
        <snl::LayerPosition::Last,   // Last layer
         snl::SrcStream<Layer5>,     // Input stream
         true,                       // Flatten input
         10,                         // Number of output colums
         Type,                       // WEIGHT_TYPE,
         snl::activator::Softmax<>,  // ACTIVATOR,
         Type,                       // BIAS_TYPE,
         snl::datatype::Auto,        // DST_TYPE
         snl::printer::Options<PrtLo,PrtLo,PrtHi>
         >;
/* ---------------------------------------------------------------------- */
/* END: Layer6                                                            */
/* ====================================================================== */


constexpr char const *Name ()  { return "Cifar10"; }
constexpr char const *File ()  { return  __FILE__; }
using     Cifar10 = snl::Network<snl::NetworkName<Name, File>
                                ,Layer0
                                ,Layer1
                                ,Layer2
                                ,Layer3
                                ,Layer4
                                ,Layer5
                                ,Layer6
                                >;

/* ---------------------------------------------------------------------- */
} /* END: namespace Cifar10                                               */
/* ---------------------------------------------------------------------- */

using SnlNetwork = cifar10::Cifar10;

#endif
     
