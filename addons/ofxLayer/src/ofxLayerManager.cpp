#include "ofxLayerManager.h"

#include "ofxLayer.h"

OFX_LAYER_BEGIN_NAMESPACE

Manager::Manager()
	: backgroundAuto(true)
{
}

void Manager::setup(int width_, int height_)
{
	width = width_;
	height = height_;

	ofFbo::Settings s;
	s.width = width;
	s.height = height;
	s.internalformat = GL_RGBA;
	frameBuffer.allocate(s);
}

void Manager::update()
{
	for (int i = 0; i < layers.size(); i++)
	{
		layers[i]->layerUpdate();
	}

	ofPushStyle();
	frameBuffer.begin();
	ofClear(0);

	vector<Layer*>::reverse_iterator it = layers.rbegin();
	while (it != layers.rend())
	{
		Layer* layer = *it;

		if (layer->isVisible())
		{
			ofPushStyle();
			ofSetColor(ofColor::white, layer->alpha * 255);
			layer->draw();
			ofPopStyle();
		}

		it++;
	}

	frameBuffer.end();
	ofPopStyle();
}

void Manager::draw()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
	frameBuffer.draw(0, 0);
	glDisable(GL_BLEND);
}

void Manager::deleteLayer(Layer* layer)
{
	assert(layer);

	vector<Layer*>::iterator it = find(layers.begin(), layers.end(), layer);
	if (it == layers.end())
	{
		layer_class_name_map.erase(layer->getClassName());
		layer_class_id_map.erase(layer->getClassID());
		layers.erase(it);
	}

	delete layer;
}

vector<string> Manager::getLayerNames()
{
	vector<string> names;
	for (int i = 0; i < layers.size(); i++)
		names.push_back(layers[i]->getClassName());
	return names;
}

const vector<Layer*>& Manager::getLayers() { return layers; }

Layer* Manager::getLayerByName(const string& name)
{
	return layer_class_name_map[name];
}

int Manager::getLayerIndexByName(const string& name)
{
	return layer_class_name_map[name]->layer_index;
}

void Manager::updateLayerIndex()
{
	for (int i = 0; i < layers.size(); i++)
	{
		layers[i]->layer_index = i;
	}
}

OFX_LAYER_END_NAMESPACE
