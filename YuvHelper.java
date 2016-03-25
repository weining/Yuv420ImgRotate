package com.weining.video.utils;

public class YuvHelper {
    static {
        try {
            System.loadLibrary("yuvimgrotate");
        } catch (UnsatisfiedLinkError e) {
            // ignore
        }
    }

    // rotate the back camera
    public static void rotateYUV420Degree90(byte[] des, byte[] data, int imageWidth,
                                            int imageHeight) {
        rotateBack(des, data, imageWidth, imageHeight);
    }

    // rotate the front camera
    public static void rotateYUV420Degree270(byte[] des, byte[] data, int imageWidth,
                                               int imageHeight) {
        rotateFront(des, data, imageWidth, imageHeight);
    }

    private static native void rotateBack(byte[] des, byte[] src, int width, int height);

    private static native void rotateFront(byte[] des, byte[] src, int width, int height);
}
