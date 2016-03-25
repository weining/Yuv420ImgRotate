#include <jni.h>
#include <ctime>
#include <stdio.h>
#include <log.h>
#ifdef __cplusplus
extern "C" {
#endif
static int length = 0;

JNIEXPORT void JNICALL Java_com_weining_video_utils_YuvHelper_rotateBack(
		JNIEnv * env, jobject thiz, jbyteArray des, jbyteArray src, jint imageWidth,
		jint imageHeight) {
	char * pSrc = (char*) env->GetByteArrayElements(src, JNI_FALSE);
	char * pDes = (char*) env->GetByteArrayElements(des, JNI_FALSE);
	int i = 0;
	int posFlag = (imageHeight - 1) * imageWidth;
	for (int x = 0; x < imageWidth; x++) {
		int pos = posFlag + x;
		for (int y = imageHeight - 1; y >= 0; y--) {
			pDes[i] = pSrc[pos];
			pos -= imageWidth;
			i++;
		}
	}
	posFlag = imageWidth * imageHeight;
	i = imageWidth * imageHeight * 3 / 2 - 1;
	for (int x = imageWidth - 1; x > 0; x -= 2) {
		int pos = posFlag;
		for (int y = 0; y < imageHeight / 2; y++) {
			pDes[i] = pSrc[pos + x];
			i--;
			pDes[i] = pSrc[pos + x - 1];
			i--;
			pos += imageWidth;
		}
	}
	env->ReleaseByteArrayElements(src, (jbyte *) pSrc, 0);
	env->ReleaseByteArrayElements(des, (jbyte *) pDes, 0);
}

JNIEXPORT void JNICALL Java_com_weining_video_utils_YuvHelper_rotateFront(
		JNIEnv * env, jobject thiz, jbyteArray des, jbyteArray src, jint imageWidth,
		jint imageHeight) {
//	if (pDes == NULL) {
	length = imageWidth * imageHeight * 3 >> 1;
//		pDes = new char[length];
//	}
	char * pSrc = (char*) env->GetByteArrayElements(src, JNI_FALSE);
	char * pDes = (char*) env->GetByteArrayElements(des, JNI_FALSE);
	int nWidth = 0, nHeight = 0;
	int wh = 0;
	int uvHeight = 0;
	if (imageWidth != nWidth || imageHeight != nHeight) {
		wh = imageWidth * imageHeight;
		uvHeight = imageHeight >> 1; // uvHeight = height / 2
	}
	// 旋转Y
//	int k = 0;
	int nPos = 0;
	int sk = imageWidth * imageHeight - 1;
	for (int i = 0; i < imageWidth; i++) {
		nPos = 0;
		for (int j = 0; j < imageHeight; j++) {
			pDes[sk]  = pSrc[nPos + i];
			sk--;
			nPos += imageWidth;
		}
	}
	sk = length - 1;
	for (int i = 0; i < imageWidth; i += 2) {
		nPos = wh;
		for (int j = 0; j < uvHeight; j++) {
			pDes[sk - 1] = pSrc[nPos + i];
			pDes[sk] = pSrc[nPos + i + 1];
			sk -= 2;
			nPos += imageWidth;
		}
	}
	env->ReleaseByteArrayElements(des, (jbyte *) pDes, 0);
	env->ReleaseByteArrayElements(src, (jbyte *) pSrc, 0);
}

#ifdef __cplusplus
}
#endif
