#include "MultNode.h"



MultNode::MultNode()
{
	//general node attributes
	Name = "Multiplication Node";
	Type = NodeType::FunctionNode;
	UniqueID = Graph::getInstance()->AssignID();
	HasCompiled = false;
	MaxNoInputs = 2;
	MaxNoOutputs = 1;

	//inputs struct creation
	for (int i = 0; i < MaxNoInputs; i++) {
		Connection InputConnection;
		InputConnection.ConnectedNode = nullptr;
		InputConnection.ConnectionIndex = -1;
		InputConnection.Value = 1;
		InputConnection.Enabled = true;
		Input.push_back(InputConnection);
	}

	//output struct creation
	Connection OutConnection;
	OutConnection.ConnectedNode = nullptr;
	OutConnection.ConnectionIndex = -1;
	OutConnection.Value = 1;
	OutConnection.Enabled = true;

	Output.push_back(OutConnection);

}


MultNode::~MultNode()
{
}


void MultNode::Compile(std::string *ShaderCode)
{

	CalculateValue();
	ShaderCode->append("\n" + CodeString());

	HasCompiled = true;
}

void MultNode::DrawNode(bool active)
{
}

float MultNode::CalculateValue()
{
	Value = 1;
	//loop through inputs and add the current values -- here it is add cause of addition node
	for (std::vector<Connection>::iterator it = Input.begin(); it != Input.end(); ++it) {
		it->Value = it->ConnectedNode->Output.at(it->ConnectionIndex).Value;
		Value *= it->Value;
	}
	Output.at(0).Value = Value;
	return Value;
}

std::string MultNode::CodeString()
{

	//need to create var names using uniqueID + nodetype name
	//std::string code   ;


	/*for (std::vector<Connection>::iterator it = Input.begin(); it != Input.end(); ++it) {

	code.append("$");
	}*/

	//not correct, i don't make use of the variables values, only the names.
	return "float $MultOut1 = $MultIn1 * $MultIn2";
}
