proc CTclBookmarksCreateWidgets { parent } {
  set frame $parent.frame

  frame $frame

  #---

  tixTree $frame.tree -width 275 -height 325 \
          -options { columns 2 header true }

  global ctcl_bookmarks_tree ctcl_bookmarks_list

  set ctcl_bookmarks_tree $frame.tree
  set ctcl_bookmarks_list [$frame.tree subwidget hlist]

  $ctcl_bookmarks_list configure -separator        @
  $ctcl_bookmarks_list configure -selectmode       single
  $ctcl_bookmarks_list configure -indicator        true
  $ctcl_bookmarks_list configure -drawbranch       true
  $ctcl_bookmarks_list configure -itemtype         imagetext
  $ctcl_bookmarks_list configure -selectbackground white
  $ctcl_bookmarks_list configure -selectforeground black

  $ctcl_bookmarks_list configure -browsecmd CTclBookmarksBrowseProc
  $ctcl_bookmarks_list configure -indicatorcmd CTclBookmarksIndicatorProc

  $ctcl_bookmarks_list header create 0 -text "Name"
  $ctcl_bookmarks_list header create 1 -text "Location"

  pack $frame.tree -side top -fill both -expand true

  #---

  pack $frame -side top -anchor w -fill both -expand true
}

proc CTclBookmarksBrowseProc { item } {
  global ctcl_bookmarks_list

  if {$item == ""} return

  set data [$ctcl_bookmarks_list info data $item]

  if {"$data" != ""} {
    exec /home/colinw/script/open_url "$data"
  }
}

proc CTclBookmarksIndicatorProc { item } {
  set type [tixEvent type]

  if { $type == "<Activate>" || $type == "<Return>" } {
    CTclBookmarksToggleGroup $item
  }
}

proc CTclBookmarksClearItems { } {
  global ctcl_bookmarks_list

  $ctcl_bookmarks_list delete all
}

proc CTclBookmarksAddGroup { path name } {
  global ctcl_bookmarks_list

  $ctcl_bookmarks_list add $path -text $name -data ""

  CTclBookmarksOpenGroup $path
}

proc CTclBookmarksAddItem { path name url } {
  global ctcl_bookmarks_list

  set path1 "$path $url"

  $ctcl_bookmarks_list add $path1 -text $name -data $url

  $ctcl_bookmarks_list item create $path1 1 -text $url
}

proc CTclBookmarksToggleGroup { path } {
  global ctcl_bookmarks_tree

  if {[$ctcl_bookmarks_tree getmode $path] == "close"} {
    CTclBookmarksCloseGroup $path
  } \
  else {
    CTclBookmarksOpenGroup $path
  }

  CTclBookmarksBrowseProc ""
}

proc CTclBookmarksOpenGroup { path } {
  global ctcl_bookmarks_tree 

  $ctcl_bookmarks_tree open $path

  $ctcl_bookmarks_tree setmode $path close
}

proc CTclBookmarksCloseGroup { path } {
  global ctcl_bookmarks_tree

  $ctcl_bookmarks_tree close $path

  $ctcl_bookmarks_tree setmode $path open
}

CTclBookmarksCreateWidgets ""

CTclBookmarksAddItems "bookmarks.html"
