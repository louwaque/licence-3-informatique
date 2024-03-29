package Exercice4;

/**
 * Le maximum d'un ensemble de formules.
 *
 * @author Loïc Escales
 *
 */
public class Maximum implements Formula {

	private Formula[] formulas;

	/**
	 * Construit Maximum.
	 *
	 * @param formulas La liste des formules en entrée.
	 */
	public Maximum(Formula[] formulas) {
		this.formulas = formulas;
	}

	@Override
	public String asString() {
		StringBuilder sb = new StringBuilder("max(");
		for (int i = 0; i < formulas.length; ++i) {
			if (i != 0) {
				sb.append(", ");
			}
			sb.append(formulas[i].asString());
		}
		sb.append(")");
		return sb.toString();
	}

	@Override
	public double asValue() {
		double value = formulas[0].asValue();
		for (int i = 1; i < formulas.length; ++i) {
			value = Math.max(value, formulas[i].asValue());
		}
		return value;
	}

}
