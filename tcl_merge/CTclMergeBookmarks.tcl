proc CTclMergeBookmarksCreateWidgets { parent } {
  set frame $parent.frame

  frame $frame

  #---

  set pane $frame.pane
  
  tixPanedWindow $pane -orientation horizontal

  $pane add left
  $pane add right
  
  set left_frame  $pane.left
  set right_frame $pane.right
  
  #----

  CTclMergeBookmarksAddTree1 $left_frame
  CTclMergeBookmarksAddTree2 $right_frame

  #---

  pack $pane -side top -fill both -expand true

  #---

  pack $frame -side top -anchor w -fill both -expand true
}

#-------

proc CTclMergeBookmarksAddTree1 { parent } {
  tixTree $parent.tree1 -width 275 -height 325 \
          -options { columns 2 header true }

  global ctcl_bookmarks_tree1 ctcl_bookmarks_list1

  set ctcl_bookmarks_tree1 $parent.tree1
  set ctcl_bookmarks_list1 [$parent.tree1 subwidget hlist]
  
  $ctcl_bookmarks_list1 configure -separator        ^
  $ctcl_bookmarks_list1 configure -selectmode       single
  $ctcl_bookmarks_list1 configure -indicator        true
  $ctcl_bookmarks_list1 configure -drawbranch       true
  $ctcl_bookmarks_list1 configure -itemtype         imagetext
  $ctcl_bookmarks_list1 configure -selectbackground white
  $ctcl_bookmarks_list1 configure -selectforeground black
  
  $ctcl_bookmarks_list1 configure -browsecmd CTclMergeBookmarksBrowseProc1
  $ctcl_bookmarks_list1 configure -indicatorcmd CTclMergeBookmarksIndicatorProc1

  $ctcl_bookmarks_list1 header create 0 -text "Name"
  $ctcl_bookmarks_list1 header create 1 -text "Location"
  
  pack $parent.tree1 -side top -fill both -expand true
}

proc CTclMergeBookmarksBrowseProc1 { item } {
  global ctcl_bookmarks_list1

  if {$item == ""} return

  set data [$ctcl_bookmarks_list1 info data $item]

  if {"$data" != ""} {
    exec /home/colinw/script/open_url "$data"
  }
}

proc CTclMergeBookmarksIndicatorProc1 { item } {
  set type [tixEvent type]

  if { $type == "<Activate>" || $type == "<Return>" } {
    CTclMergeBookmarksToggleGroup1 $item
  }
}

proc CTclMergeBookmarksClearItems1 { } {
  global ctcl_bookmarks_list1

  $ctcl_bookmarks_list1 delete all
}

proc CTclMergeBookmarksAddGroup1 { path name } {
  global ctcl_bookmarks_list1

  $ctcl_bookmarks_list1 add $path -text $name -data ""

  CTclMergeBookmarksOpenGroup1 $path
}

proc CTclMergeBookmarksAddItem1 { path name url } {
  global ctcl_bookmarks_list1

  $ctcl_bookmarks_list1 add $path -text $name -data $url

  $ctcl_bookmarks_list1 item create $path 1 -text $url
}

proc CTclMergeBookmarksToggleGroup1 { path } {
  global ctcl_bookmarks_tree1

  if {[$ctcl_bookmarks_tree1 getmode $path] == "close"} {
    CTclMergeBookmarksCloseGroup1 $path
  } \
  else {
    CTclMergeBookmarksOpenGroup1 $path
  }

  CTclMergeBookmarksBrowseProc1 ""
}

proc CTclMergeBookmarksOpenGroup1 { path } {
  global ctcl_bookmarks_tree1 

  $ctcl_bookmarks_tree1 open $path

  $ctcl_bookmarks_tree1 setmode $path close
}

proc CTclMergeBookmarksCloseGroup1 { path } {
  global ctcl_bookmarks_tree1

  $ctcl_bookmarks_tree1 close $path

  $ctcl_bookmarks_tree1 setmode $path open
}

proc CTclMergeBookmarksSetGroupColor1 { path color } {
  global ctcl_bookmarks_list1

  set style [tixDisplayStyle imagetext -fg $color]

  $ctcl_bookmarks_list1 entryconfigure $path -style $style
}

proc CTclMergeBookmarksSetBookmarkColor1 { path color } {
  global ctcl_bookmarks_list1

  set style [tixDisplayStyle imagetext -fg $color]

  $ctcl_bookmarks_list1 entryconfigure $path -style $style
}

#-------

proc CTclMergeBookmarksAddTree2 { parent } {
  tixTree $parent.tree2 -width 275 -height 325 \
          -options { columns 2 header true }

  global ctcl_bookmarks_tree2 ctcl_bookmarks_list2

  set ctcl_bookmarks_tree2 $parent.tree2
  set ctcl_bookmarks_list2 [$parent.tree2 subwidget hlist]
  
  $ctcl_bookmarks_list2 configure -separator        ^
  $ctcl_bookmarks_list2 configure -selectmode       single
  $ctcl_bookmarks_list2 configure -indicator        true
  $ctcl_bookmarks_list2 configure -drawbranch       true
  $ctcl_bookmarks_list2 configure -itemtype         imagetext
  $ctcl_bookmarks_list2 configure -selectbackground white
  $ctcl_bookmarks_list2 configure -selectforeground black
  
  $ctcl_bookmarks_list2 configure -browsecmd CTclMergeBookmarksBrowseProc2
  $ctcl_bookmarks_list2 configure -indicatorcmd CTclMergeBookmarksIndicatorProc2

  $ctcl_bookmarks_list2 header create 0 -text "Name"
  $ctcl_bookmarks_list2 header create 1 -text "Location"
  
  pack $parent.tree2 -side top -fill both -expand true
}

proc CTclMergeBookmarksBrowseProc2 { item } {
  global ctcl_bookmarks_list2

  if {$item == ""} return

  set data [$ctcl_bookmarks_list2 info data $item]

  if {"$data" != ""} {
    exec /home/colinw/script/open_url "$data"
  }
}

proc CTclMergeBookmarksIndicatorProc2 { item } {
  set type [tixEvent type]

  if { $type == "<Activate>" || $type == "<Return>" } {
    CTclMergeBookmarksToggleGroup2 $item
  }
}

proc CTclMergeBookmarksClearItems2 { } {
  global ctcl_bookmarks_list2

  $ctcl_bookmarks_list2 delete all
}

proc CTclMergeBookmarksAddGroup2 { path name } {
  global ctcl_bookmarks_list2

  $ctcl_bookmarks_list2 add $path -text $name -data ""

  CTclMergeBookmarksOpenGroup2 $path
}

proc CTclMergeBookmarksAddItem2 { path name url } {
  global ctcl_bookmarks_list2

  $ctcl_bookmarks_list2 add $path -text $name -data $url

  $ctcl_bookmarks_list2 item create $path 1 -text $url
}

proc CTclMergeBookmarksToggleGroup2 { path } {
  global ctcl_bookmarks_tree2

  if {[$ctcl_bookmarks_tree2 getmode $path] == "close"} {
    CTclMergeBookmarksCloseGroup2 $path
  } \
  else {
    CTclMergeBookmarksOpenGroup2 $path
  }

  CTclMergeBookmarksBrowseProc2 ""
}

proc CTclMergeBookmarksOpenGroup2 { path } {
  global ctcl_bookmarks_tree2 

  $ctcl_bookmarks_tree2 open $path

  $ctcl_bookmarks_tree2 setmode $path close
}

proc CTclMergeBookmarksCloseGroup2 { path } {
  global ctcl_bookmarks_tree2

  $ctcl_bookmarks_tree2 close $path

  $ctcl_bookmarks_tree2 setmode $path open
}

proc CTclMergeBookmarksSetGroupColor2 { path color } {
  global ctcl_bookmarks_list2
  
  set style [tixDisplayStyle imagetext -fg $color]
  
  $ctcl_bookmarks_list2 entryconfigure $path -style $style
}

proc CTclMergeBookmarksSetBookmarkColor2 { path color } {
  global ctcl_bookmarks_list2

  set style [tixDisplayStyle imagetext -fg $color]

  $ctcl_bookmarks_list2 entryconfigure $path -style $style
}

#-------

CTclMergeBookmarksCreateWidgets ""

CTclMergeBookmarksAddItems1 "bookmarks1.html"
CTclMergeBookmarksAddItems2 "bookmarks2.html"

CTclMergeBookmarksHighlight
