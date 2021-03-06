#ifndef __CANVASCONTEXT_2D__
#define __CANVASCONTEXT_2D__

#include "SkCanvas.h"
#include "string"
#include "vector"
#include "AffineTransform.h"
#include "passrefptr.h"
#include "graphicstypes.h"
#include "Color.h"
#include "CanvasStyle.h"
#include "PassOwnPtr.h"
#include "FontDescription.h"
#include "ImageData.h"

using namespace Canvas2D;
class BitmapImage;

class CanvasContext2D
{
public:
	void deref() {};
	static PassOwnPtr<CanvasContext2D> create(SkCanvas *canvas)
	{
		return adoptPtr(new CanvasContext2D(canvas));
	}
	CanvasContext2D(SkCanvas*);
	virtual ~CanvasContext2D();

	CanvasStyle *strokeStyle() const;
	void setStrokeStyle(PassRefPtr<CanvasStyle>);
	void applyStokeColor(PassRefPtr<CanvasStyle>);
	
	CanvasStyle* fillStyle() const;
	void setFillStyle(PassRefPtr<CanvasStyle>);
	void applyFillColor(PassRefPtr<CanvasStyle>);

	float lineWidth() const;
	void setLineWidth(float);

	std::string lineCap() const;
	void setLineCap(const std::string&);
	LineCap getLineCap() const { return state().m_lineCap; }
	
	std::string lineJoin() const;
	void setLineJoin(const std::string&);
	LineJoin getLineJoin() const { return state().m_lineJoin; }

	float miterLimit() const;
	void setMiterLimit(float);

	const std::vector<float>& getLineDash() const;
	void setLineDash(const std::vector<float>&);

	float lineDashOffset() const;
	void setLineDashOffset(float);

	float shadowOffsetX() const;
	void setShadowOffsetX(float);

	float shadowOffsetY() const;
	void setShadowOffsetY(float);

	float shadowBlur() const;
	void setShadowBlur(float);

	std::string shadowColor() const;
	void setShadowColor(const std::string&);

	float globalAlpha() const;
	void setGlobalAlpha(float);

	std::string globalCompositeOperation() const;
	void setGlobalCompositeOperation(const std::string&);

	void save();
	void restore();

	PassRefPtr<AffineTransform> currentTransform() const
	{
		return adoptRef(new AffineTransform(state().m_transform));
	}
	void setCurrentTransform(PassRefPtr<AffineTransform>);

	void scale(float sx, float sy);
	void rotate(float angleInRadians);
	void translate(float tx, float ty);
	void transform(float m11, float m12, float m21, float m22, float dx, float dy);
	void setTransform(float m11, float m12, float m21, float m22, float dx, float dy);
	void resetTransform();

	void setStrokeColor(const std::string& color);
	void setStrokeColor(float grayLevel);
	void setStrokeColor(const std::string& color, float alpha);
	void setStrokeColor(float grayLevel, float alpha);
	void setStrokeColor(float r, float g, float b, float a);
	void setStrokeColor(float c, float m, float y, float k, float a);

	void setFillColor(const std::string &color);
	void setFillColor(float grayLevel);
	void setFillColor(const std::string& color, float alpha);
	void setFillColor(float grayLevel, float alpha);
	void setFillColor(float r, float g, float b, float a);
	void setFillColor(float c, float m, float y, float k, float a);

	void beginPath();
	void closePath();
	void moveTo(float x, float y);
	void lineTo(float x, float y);
	void quadraticCurveTo(float cpx, float cpy, float x, float y);
	void bezierCurveTo(float cp1x, float cp1y, float cp2x, float cp2y, float x, float y);
	void arcTo(float x1, float y1, float x2, float y2, float radius);
	void arc(float x, float y, float radius, float startAngle, float endAngle, bool anticlockwise);
	void ellipse(float x, float y, float radiusX, float radiusY, float rotation, float startAngle, float endAngle, bool anticlockwise);
	void rect(float x, float y, float width, float height);

	void addEllipse(const FloatPoint&, float radiusX, float radiusY, float startAngle, float endAngle, bool anticlockwise);

	void fill(const std::string& winding = "nonzero");
	void stroke();
	void clip(const std::string& winding = "nonzero");
	bool isPointInPath(const float x, const float y, const std::string& winding = "nonzero");
	void clearRect(float x, float y, float width, float height);
	void fillRect(float x, float y, float width, float height);
	void strokeRect(float x, float y, float width, float height);
	void drawImage(BitmapImage*, float x, float y);
	PassRefPtr<CanvasGradient> createLinearGradient(float x0, float y0, float x1, float y1);
	PassRefPtr<CanvasGradient> createRadialGradient(float x0, float y0, float r0, float x1, float y1, float r1);
	PassRefPtr<CanvasPattern> createPattern(PassRefPtr<BitmapImage>, const std::string& repetitionType);

	PassRefPtr<ImageData> createImageData(float width, float height) const;
	PassRefPtr<ImageData> getImageData(float sx, float sy, float sw, float sh) const;
	void putImageData(PassRefPtr<ImageData>, float dx, float dy);

	void reset();

	std::string font() const;
	void setFont(const std::string&);

	std::string textAlign() const;
	void setTextAlign(const std::string&);

	std::string textBaseline() const;
	void setTextBaseline(const std::string&);

	void fillText(const char* text, float x, float y);
	void strokeText( const char* text, float x, float y);
	float measureText(const std::string& text);

	bool imageSmoothingEnabled() const;
	void setImageSmoothingEnabled(bool);

private:
	bool hasCurrentPoint() const;
	SkPoint currentPoint() const;
	SkColor applyAlpha(SkColor c) const;

	struct State
	{
		State();
		virtual ~State();

		State(const State&);
		State& operator=(const State&);

		unsigned m_unrealizedSaveCount;

		std::string m_unparsedStrokeColor;
		std::string m_unparsedFillColor;
		RefPtr<CanvasStyle> m_strokeStyle;
		RefPtr<CanvasStyle> m_fillStyle;
		float m_lineWidth;
		LineCap m_lineCap;
		LineJoin m_lineJoin;
		float m_miterLimit;
		FloatSize m_shadowOffset;
		float m_shadowBlur;
		RGBA32 m_shadowColor;
		float m_globalAlpha;
		CompositeOperator m_globalComposite;
		WebBlendMode m_globalBlend;
		AffineTransform m_transform;
		bool m_invertibleCTM;
		std::vector<float> m_lineDash;
		float m_lineDashOffset;
		bool m_imageSmoothingEnabled;

		// Text state.
		TextAlign m_textAlign;
		TextBaseline m_textBaseline;

		std::string m_unparsedFont;
		FontDescription m_FontDescription;
		bool m_realizedFont;
	};

	State& modifiableState() { return m_stateStack.back(); }
	const State& state() const { return m_stateStack.back(); }

	void applyShadow();
	bool shouldDrawShadows() const;

	int getFontBaseline(const SkPaint&) const;

	void clearCanvas();
	bool rectContainsTransformedRect(const FloatRect&, const FloatRect&) const;

	void inflateStrokeRect(FloatRect&) const;

	template<class T> void fullCanvasCompositedFill(const T&);

	virtual bool is2d() const { return true; }
	virtual bool isAccelerated() const;
	virtual bool hasAlpha() const { return m_hasAlpha; }

	virtual bool isTransformInvertible() const { return state().m_invertibleCTM; }

	std::vector<State> m_stateStack;
	bool m_usesCSSCompatibilityParseMode;
	bool m_hasAlpha;
	//MutableStylePropertyMap m_fetchedFonts;

	// add by hgl
	SkCanvas *m_pCanvas;

	SkPath m_path;
	Color m_fillColor;
	Color m_strokeColor;
	SkPaint m_strokePaint;
	SkPaint m_fillPaint;


};

#endif

