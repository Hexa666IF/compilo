// Generated from /home/sadsitha/Documents/Code/School/Compilo/compilo/compiler/ifcc.g4 by ANTLR 4.7.1
import org.antlr.v4.runtime.Lexer;
import org.antlr.v4.runtime.CharStream;
import org.antlr.v4.runtime.Token;
import org.antlr.v4.runtime.TokenStream;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.misc.*;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast"})
public class ifccLexer extends Lexer {
	static { RuntimeMetaData.checkVersion("4.7.1", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		T__0=1, T__1=2, T__2=3, T__3=4, T__4=5, T__5=6, T__6=7, EXPR=8, TERM=9, 
		F=10, RETURN=11, CONST=12, COMMENT=13, DIRECTIVE=14, WS=15;
	public static String[] channelNames = {
		"DEFAULT_TOKEN_CHANNEL", "HIDDEN"
	};

	public static String[] modeNames = {
		"DEFAULT_MODE"
	};

	public static final String[] ruleNames = {
		"T__0", "T__1", "T__2", "T__3", "T__4", "T__5", "T__6", "EXPR", "TERM", 
		"F", "RETURN", "CONST", "COMMENT", "DIRECTIVE", "WS"
	};

	private static final String[] _LITERAL_NAMES = {
		null, "'int'", "'main'", "'('", "')'", "'{'", "';'", "'}'", null, null, 
		null, "'return'"
	};
	private static final String[] _SYMBOLIC_NAMES = {
		null, null, null, null, null, null, null, null, "EXPR", "TERM", "F", "RETURN", 
		"CONST", "COMMENT", "DIRECTIVE", "WS"
	};
	public static final Vocabulary VOCABULARY = new VocabularyImpl(_LITERAL_NAMES, _SYMBOLIC_NAMES);

	/**
	 * @deprecated Use {@link #VOCABULARY} instead.
	 */
	@Deprecated
	public static final String[] tokenNames;
	static {
		tokenNames = new String[_SYMBOLIC_NAMES.length];
		for (int i = 0; i < tokenNames.length; i++) {
			tokenNames[i] = VOCABULARY.getLiteralName(i);
			if (tokenNames[i] == null) {
				tokenNames[i] = VOCABULARY.getSymbolicName(i);
			}

			if (tokenNames[i] == null) {
				tokenNames[i] = "<INVALID>";
			}
		}
	}

	@Override
	@Deprecated
	public String[] getTokenNames() {
		return tokenNames;
	}

	@Override

	public Vocabulary getVocabulary() {
		return VOCABULARY;
	}


	public ifccLexer(CharStream input) {
		super(input);
		_interp = new LexerATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}

	@Override
	public String getGrammarFileName() { return "ifcc.g4"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public String[] getChannelNames() { return channelNames; }

	@Override
	public String[] getModeNames() { return modeNames; }

	@Override
	public ATN getATN() { return _ATN; }

	public static final String _serializedATN =
		"\3\u608b\ua72a\u8133\ub9ed\u417c\u3be7\u7786\u5964\2\21z\b\1\4\2\t\2\4"+
		"\3\t\3\4\4\t\4\4\5\t\5\4\6\t\6\4\7\t\7\4\b\t\b\4\t\t\t\4\n\t\n\4\13\t"+
		"\13\4\f\t\f\4\r\t\r\4\16\t\16\4\17\t\17\4\20\t\20\3\2\3\2\3\2\3\2\3\3"+
		"\3\3\3\3\3\3\3\3\3\4\3\4\3\5\3\5\3\6\3\6\3\7\3\7\3\b\3\b\3\t\3\t\3\t\3"+
		"\t\3\t\3\t\3\t\3\t\3\t\5\t>\n\t\3\n\3\n\3\n\3\n\3\n\3\n\3\n\3\n\3\n\5"+
		"\nI\n\n\3\13\3\13\3\13\3\13\3\13\5\13P\n\13\3\f\3\f\3\f\3\f\3\f\3\f\3"+
		"\f\3\r\6\rZ\n\r\r\r\16\r[\3\16\3\16\3\16\3\16\7\16b\n\16\f\16\16\16e\13"+
		"\16\3\16\3\16\3\16\3\16\3\16\3\17\3\17\7\17n\n\17\f\17\16\17q\13\17\3"+
		"\17\3\17\3\17\3\17\3\20\3\20\3\20\3\20\4co\2\21\3\3\5\4\7\5\t\6\13\7\r"+
		"\b\17\t\21\n\23\13\25\f\27\r\31\16\33\17\35\20\37\21\3\2\4\3\2\62;\5\2"+
		"\13\f\17\17\"\"\2\u0081\2\3\3\2\2\2\2\5\3\2\2\2\2\7\3\2\2\2\2\t\3\2\2"+
		"\2\2\13\3\2\2\2\2\r\3\2\2\2\2\17\3\2\2\2\2\21\3\2\2\2\2\23\3\2\2\2\2\25"+
		"\3\2\2\2\2\27\3\2\2\2\2\31\3\2\2\2\2\33\3\2\2\2\2\35\3\2\2\2\2\37\3\2"+
		"\2\2\3!\3\2\2\2\5%\3\2\2\2\7*\3\2\2\2\t,\3\2\2\2\13.\3\2\2\2\r\60\3\2"+
		"\2\2\17\62\3\2\2\2\21=\3\2\2\2\23H\3\2\2\2\25O\3\2\2\2\27Q\3\2\2\2\31"+
		"Y\3\2\2\2\33]\3\2\2\2\35k\3\2\2\2\37v\3\2\2\2!\"\7k\2\2\"#\7p\2\2#$\7"+
		"v\2\2$\4\3\2\2\2%&\7o\2\2&\'\7c\2\2\'(\7k\2\2()\7p\2\2)\6\3\2\2\2*+\7"+
		"*\2\2+\b\3\2\2\2,-\7+\2\2-\n\3\2\2\2./\7}\2\2/\f\3\2\2\2\60\61\7=\2\2"+
		"\61\16\3\2\2\2\62\63\7\177\2\2\63\20\3\2\2\2\64\65\5\23\n\2\65\66\7-\2"+
		"\2\66\67\5\21\t\2\67>\3\2\2\289\5\23\n\29:\7/\2\2:;\5\21\t\2;>\3\2\2\2"+
		"<>\5\23\n\2=\64\3\2\2\2=8\3\2\2\2=<\3\2\2\2>\22\3\2\2\2?@\5\25\13\2@A"+
		"\7,\2\2AB\5\23\n\2BI\3\2\2\2CD\5\25\13\2DE\7\61\2\2EF\5\23\n\2FI\3\2\2"+
		"\2GI\5\25\13\2H?\3\2\2\2HC\3\2\2\2HG\3\2\2\2I\24\3\2\2\2JP\5\31\r\2KL"+
		"\7*\2\2LM\5\21\t\2MN\7+\2\2NP\3\2\2\2OJ\3\2\2\2OK\3\2\2\2P\26\3\2\2\2"+
		"QR\7t\2\2RS\7g\2\2ST\7v\2\2TU\7w\2\2UV\7t\2\2VW\7p\2\2W\30\3\2\2\2XZ\t"+
		"\2\2\2YX\3\2\2\2Z[\3\2\2\2[Y\3\2\2\2[\\\3\2\2\2\\\32\3\2\2\2]^\7\61\2"+
		"\2^_\7,\2\2_c\3\2\2\2`b\13\2\2\2a`\3\2\2\2be\3\2\2\2cd\3\2\2\2ca\3\2\2"+
		"\2df\3\2\2\2ec\3\2\2\2fg\7,\2\2gh\7\61\2\2hi\3\2\2\2ij\b\16\2\2j\34\3"+
		"\2\2\2ko\7%\2\2ln\13\2\2\2ml\3\2\2\2nq\3\2\2\2op\3\2\2\2om\3\2\2\2pr\3"+
		"\2\2\2qo\3\2\2\2rs\7\f\2\2st\3\2\2\2tu\b\17\2\2u\36\3\2\2\2vw\t\3\2\2"+
		"wx\3\2\2\2xy\b\20\3\2y \3\2\2\2\t\2=HO[co\4\b\2\2\2\3\2";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}