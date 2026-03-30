
#import "@preview/basic-report:0.4.0": *

// Colors
#let accent     = rgb("#3b82f6")  // heading + link colour
#let code-bg    = rgb("#f1f5f9")  // inline code background
#let code-color = rgb("#d32677")  // inline code text colour


#show: it => basic-report(
  doc-category: "Specification",
  doc-title: "Generic Graph",
  author: "Milán Várady",
  affiliation: "Budapest Unversity of Technology and Economics",
  language: "en",
  compact-mode: false,
  heading-font: "Lato",
  heading-color: accent,
  datetime-fmt: "[year].[month].[day]",
  it
)

// Links
#show link: it => text(fill: accent)[#it]

// Inline code
#show raw.where(block: false): it => box(
  fill: code-bg,
  inset: (x: 4pt, y: 2pt),
  radius: 3pt,
  text(fill: code-color, font: "FiraCode Nerd Font Mono", size: 0.9em)[#it]
)
