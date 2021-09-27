#ifndef FUNCTIONPLOTTER_H
#define FUNCTIONPLOTTER_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class FunctionPlotter; }
QT_END_NAMESPACE

class FunctionPlotter : public QMainWindow
{
    Q_OBJECT

public:
    FunctionPlotter(QWidget *parent = nullptr);
    ~FunctionPlotter();

private:
    Ui::FunctionPlotter *ui;

    /**
     * Initializes the user display with appropriate settings
     */
    void setupDisplay();

    /**
     * Checks if given equation is invalid and displays error MessageBox to the user
     * @param equation String variable containing equation to be validated
     * @return Returns true if the equation is valid
     */
    bool validateEquation(std::string &equation);

    /**
     * Helper function for validateEquation(). Checks if string contains valid equation.
     * @param equation String variable containing equation to be validated
     * @return Returns true if the equation is valid
     */
    bool isValidEquation(std::string &equation);

    /**
     * Checks whether the given character is a supported mathematical operator
     * @param ch Character variable containing character to be checked
     * @return Returns true if the character is a supported operator
     */
    bool isOperator(char ch);

    /**
     * Checks if the given character is a digit, x or X
     * @param ch Character variable containing character to be checked
     * @return Returns true if the character is a digit, x or X
     */
    bool isDigitOrX(char ch);

    /**
     * Checks if the given character is x or X
     * @param ch Character variable containing character to be checked
     * @return Returns true if the character is x or X
     */
    bool isCharacterX(char ch);

private slots:

    /**
     * Plots the given equation on the graph
     */
    void onPlotButtonClick();

};
#endif // FUNCTIONPLOTTER_H
