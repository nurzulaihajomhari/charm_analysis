# charm_analysis

This is repository for 7 TeV analysis: Measurement of total and differential charm cross-sections with the CMS detector.

The charm analysis is measured through the decay of D* to D0 and pion.

The codes description are as follows:

1. Decay_sketch.png: an illustration of D* decays to D0 and pion using LibreOffice Impress.

2. Func.h: header file contains modified gaussian function and Granet function. 

3. Nsignal_extraction.cc: This code extract D* signal and using background subtraction method and fitting function called in Func.h.

4. Nsignal_tablev1.cc: An example on how to plot 2D table.

5. PlotUtil.h: Header file contains all the options for histogram/graph styling.

6. Xsec2D_tablev1.cxx: individual code to plot cross-section in 2D table

7. Xsec_proXYv2.cc: Plotted charm cross-section as a function of transverse momentum

8. phase_space_general.cxx: Used to illustrate the project's idea using ROOT. Produced phase_graph.pdf.


The publication of the analysis:
https://cms-results.web.cern.ch/cms-results/public-results/preliminary-results/BPH-22-007/index.html
