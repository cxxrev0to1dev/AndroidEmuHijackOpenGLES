import os,sys,difflib

def GLESStringFilterFromIDAPro(infile,outfile):
  list1 = []
  outF = open(outfile, "w")
  with open(infile) as f:
      for line in f:
        if "gl" in line:
          line = line.replace(' ', '-', 1)
          # line = line.replace('gl', '-gl', 1)
          line = line[0:line.index("-")]
          list1.append(line)
          outF.write(line)
          outF.write("\n")
  print list1
def EGLStringFilterFromIDAPro(infile,outfile):
  list1 = []
  outF = open(outfile, "w")
  with open(infile) as f:
      for line in f:
        if "egl" in line:
          line = line.replace(' ', '-', 1)
          # line = line.replace('gl', '-gl', 1)
          line = line[0:line.index("-")]
          list1.append(line)
          outF.write(line)
          outF.write("\n")
  print list1
def GLESv1StringFilterFromIDAPro(infile,outfile):
  list1 = []
  outF = open(outfile, "w")
  with open(infile) as f:
      for line in f:
        list1 = line.split("gl")
        break
  for line in list1:
    line = line.replace(' ', '')
    linesss = "gl"+ line
    outF.write(linesss)
    outF.write("\n")
  print list1
def Diff(infile1,infile2):
  if os.path.isfile(infile1)==True and os.path.isfile(infile2)==True:
    with open(infile1) as f:
        t1 = f.read().splitlines()
        t1s = set(t1)
    with open(infile2) as f:
        t2 = f.read().splitlines()
        t2s = set(t2)
    for diff in t1s-t2s:
        # print t1.index(diff), diff
        print '---',diff,'---'  
def GLESFilter():
  outfile1 = "/media/dengtao/win_software/win_software/android5.1_rk3288/device/generic/goldfish/RedFingerOpenGLES/tools/api_check/gles1_hardware_dst.txt"
  infile1 = "/media/dengtao/win_software/win_software/android5.1_rk3288/device/generic/goldfish/RedFingerOpenGLES/tools/api_check/gles1_hardware_src.txt"
  outfile2 = "/media/dengtao/win_software/win_software/android5.1_rk3288/device/generic/goldfish/RedFingerOpenGLES/tools/api_check/gles2_hardware_dst.txt"
  infile2 = "/media/dengtao/win_software/win_software/android5.1_rk3288/device/generic/goldfish/RedFingerOpenGLES/tools/api_check/gles2_hardware_src.txt"
  if os.path.isfile(outfile1)==True and os.path.isfile(outfile2)==True:
    with open(outfile1) as f:
        t1 = f.read().splitlines()
        t1s = set(t1)
    with open(outfile2) as f:
        t2 = f.read().splitlines()
        t2s = set(t2)
    for diff in t1s-t2s:
        # print t1.index(diff), diff
        print '---',diff,'---'
  else:
    GLESStringFilterFromIDAPro(infile1,outfile1)
    GLESStringFilterFromIDAPro(infile2,outfile2)
def EGLFilter():
  infile1 = "/media/dengtao/win_software/win_software/android5.1_rk3288/device/generic/goldfish/RedFingerOpenGLES/tools/api_check/egl_api_src.txt"
  outfile1 = "/media/dengtao/win_software/win_software/android5.1_rk3288/device/generic/goldfish/RedFingerOpenGLES/tools/api_check/egl_api_dst.txt"
  EGLStringFilterFromIDAPro(infile1,outfile1)
def GLESv1Filter():
  infile1 = "/media/dengtao/win_software/win_software/android5.1_rk3288/device/generic/goldfish/RedFingerOpenGLES/tools/api_check/glesv1_src.txt"
  outfile1 = "/media/dengtao/win_software/win_software/android5.1_rk3288/device/generic/goldfish/RedFingerOpenGLES/tools/api_check/glesv1_dst.txt"
  GLESv1StringFilterFromIDAPro(infile1,outfile1)

difffile1 = "/media/dengtao/win_software/win_software/android5.1_rk3288/device/generic/goldfish/RedFingerOpenGLES/tools/api_check/glesv1_dst.txt"
difffile2 = "/media/dengtao/win_software/win_software/android5.1_rk3288/device/generic/goldfish/RedFingerOpenGLES/tools/api_check/gles2_hardware_dst.txt"
Diff(difffile1,difffile2)