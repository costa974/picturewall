## DESCRIPTION / FEATURE ##

Picture Wall is Qt based application to view local images as well as search queried images on google.com with rich set of UI

This application is developed using Qt4.5.0
  * Cross compile
  * Browse local images as well as search images on google.com
  * interactive UI
  * Animated image zoom in and zoom out on mouse pressed
  * Entire images zoom in and zoom out on mouse wheel
  * Horizontal scrolling of images on mouse drag in respective horizontal direction
  * Fast loading of images on view using QtConcurrent

<table><tr><td><a href='http://picasaweb.google.co.in/lh/photo/2IOEuifrYAyuT3ZGwRzywQ?feat=embedwebsite'><img src='http://lh4.ggpht.com/_MIDp0xgQguY/SgArGGdj46I/AAAAAAAAACk/9Oxybxl9zoI/s800/snapshot2.png' /></a></td></tr><tr><td>For More<a href='http://picasaweb.google.co.in/vishwajeet.dusane/PictureWall?feat=embedwebsite'> ScreenShots - PictureWall</a></td></tr></table>


## HOW TO BUILD?: ##

### Linux: ###
> qmake (same or higher version of  Qt4.5.0)

> make
### Windows: ###
> qmake (same or higher version of Qt4.5.0)

> nmake

cd bin

RUN "picturewall" binary from this directory


## KNOWN ISSUES/BUGS: ##

  * When search query is submitted on google server, and search option is changed to local image browse,still search queries are popupated inside view.

> This is because when result are fetched from the google server are still downloading and once the download of those thumbnail view images are done, those images are populated inside view regardless wheather view is changed to other view or other search query.

  * Google search images might get duplicate images, i.e. Imagse populated inside view might be duplicated

> This is cause of the query sent over google server returns searched result which has duplicate image URL

Please report for bugs/Feature improvement/new feature at vishwajeet.dusane@gmail.com

## HARDWARE/SOFTWARE: ##

Build on Linux (Kubuntu 8.10) with Qt4.5.0 library and KDevelop


## DEVELOPER: ##

Vishwajeet Dusane vishwajeet.dusane@gmail.com